/*
Copyright (C) 2023 Jacob Gibson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <audio/sound_buffer.h>

#include <climits>
#include <cstdlib>
#include <stdio.h>

#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>

SoundBuffer* SoundBuffer::get() {
  static SoundBuffer* pSndBuf = new SoundBuffer();
  return pSndBuf;
}

ALuint SoundBuffer::AddSoundEffect(const char* kFilename) {
  ALenum err, format;
  ALuint buffer;
  SNDFILE* pSndFile;
  SF_INFO sf_info;
  short* pMembuf;
  sf_count_t num_frames;
  ALsizei num_bytes;

  /* Open the audio file and check that it's usable. */
  pSndFile = sf_open(kFilename, SFM_READ, &sf_info);
  if (!pSndFile) {
    fprintf(stderr, "Could not open audio in %s: %s\n", 
            kFilename, sf_strerror(pSndFile));
    return 0;
  }
  if (sf_info.frames < 1 || sf_info.frames > 
    (sf_count_t)(INT_MAX / sizeof(short)) / sf_info.channels) {
    fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", 
            kFilename, sf_info.frames);
    sf_close(pSndFile);
    return 0;
  }

  /* Get the sound format, and figure out the OpenAL format */
  format = AL_NONE;
  if (sf_info.channels == 1){
    format = AL_FORMAT_MONO16;
  } else if (sf_info.channels == 2) {
    format = AL_FORMAT_STEREO16;
  } else if (sf_info.channels == 3) {
    if (sf_command(pSndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == 
      SF_AMBISONIC_B_FORMAT)
      format = AL_FORMAT_BFORMAT2D_16;
  } else if (sf_info.channels == 4) {
    if (sf_command(pSndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == 
      SF_AMBISONIC_B_FORMAT)
      format = AL_FORMAT_BFORMAT3D_16;
  }
  if (!format) {
    fprintf(stderr, "Unsupported channel count: %d\n", sf_info.channels);
    sf_close(pSndFile);
    return 0;
  }

  /* Decode the whole audio file to a buffer. */
  pMembuf = static_cast<short*>(malloc((size_t)(sf_info.frames * 
                            sf_info.channels) * sizeof(short)));

  num_frames = sf_readf_short(pSndFile, pMembuf, sf_info.frames);
  if (num_frames < 1) {
    free(pMembuf);
    sf_close(pSndFile);
    fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", 
            kFilename, num_frames);
    return 0;
  }
  num_bytes = (ALsizei)(num_frames * sf_info.channels) * 
              (ALsizei)sizeof(short);

  /* Buffer the audio data into a new buffer object, then free the data and
   * close the file.
   */
  buffer = 0;
  alGenBuffers(1, &buffer);
  alBufferData(buffer, format, pMembuf, num_bytes, sf_info.samplerate);

  free(pMembuf);
  sf_close(pSndFile);

  /* Check if an error occured, and clean up if so. */
  err = alGetError();
  if (err != AL_NO_ERROR) {
    fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
    if (buffer && alIsBuffer(buffer))
      alDeleteBuffers(1, &buffer);
    return 0;
  }

  pSoundEffectBuffers_.push_back(buffer);  // add to the list of known buffers

  return buffer;
}

bool SoundBuffer::RemoveSoundEffect(const ALuint& kBuffer) {
  auto it = pSoundEffectBuffers_.begin();
  while (it != pSoundEffectBuffers_.end()) {
    if (*it == kBuffer) {
      alDeleteBuffers(1, &*it);

      it = pSoundEffectBuffers_.erase(it);

      return true;
    } else {
      ++it;
    }
  }
  return false;  // couldn't find to remove
}


SoundBuffer::SoundBuffer() {
  pSoundEffectBuffers_.clear();
}

SoundBuffer::~SoundBuffer() {
  alDeleteBuffers(pSoundEffectBuffers_.size(), pSoundEffectBuffers_.data());

  pSoundEffectBuffers_.clear();
}