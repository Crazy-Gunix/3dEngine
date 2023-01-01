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

#include <audio/music_buffer.h>

#include <cstddef>
#include <malloc.h>

#include <AL/alext.h>

void MusicBuffer::Play() {
  ALsizei i;

  /* clear any errors */
  alGetError();

  /* Rewind the source position and clear the buffer queue */  
  alSourceRewind(pSource_);
  alSourcei(pSource_, AL_BUFFER, 0);

  /* Fill the buffer queue */
  for (i = 0; i < kNumBuffers_; i++) {
    /* Get some data to give it to the buffer. */
    sf_count_t slen = sf_readf_short(pSndFile_, pMembuf_, kBufferSamples_);
    if (slen < 1) break;

    slen *= pSfInfo_.channels * (sf_count_t)sizeof(short);
    alBufferData(pBuffers_[i], pFormat_, pMembuf_, 
                (ALsizei)slen, pSfInfo_.samplerate);
  }
  if (alGetError() != AL_NO_ERROR)
    throw("Error buffering for playback");

  /* Now queue and start playback! */
  alSourceQueueBuffers(pSource_, i, pBuffers_);
  alSourcePlay(pSource_);
  if (alGetError() != AL_NO_ERROR)
    throw("Error starting playback");
}

// void MusicBuffer::Pause() {
//
// }

// void MusicBuffer::Stop() {
//
// }

void MusicBuffer::UpdateBufferStream() {
  ALint processed, state;

  // clear error
  alGetError();
  /* Get relevant source info */
  alGetSourcei(pSource_, AL_SOURCE_STATE, &state);
  alGetSourcei(pSource_, AL_BUFFERS_PROCESSED, &processed);
  if (alGetError() != AL_NO_ERROR)
    throw("Error checking music source state");
  
  /* Unqueue and handle each processed buffer */
  while (processed > 0) {
    ALuint bufid;
    sf_count_t slen;

    alSourceUnqueueBuffers(pSource_, 1, &bufid);
    processed--;

    /* Read the next chunk of data, refill the buffer, and queue it back on the source */
    slen = sf_readf_short(pSndFile_, pMembuf_, kBufferSamples_);
    if (slen>0) {
      slen *= pSfInfo_.channels * (sf_count_t)sizeof(short);
      alBufferData(bufid, pFormat_, pMembuf_, 
                  (ALsizei)slen, pSfInfo_.samplerate);
      alSourceQueueBuffers(pSource_, 1, &bufid);
    }
    if (alGetError() != AL_NO_ERROR)
      throw("error buffering music data");
  }

  /* Make sure that the source has not underrun */
  if (state != AL_PLAYING && state != AL_PAUSED) {
    ALint queued;

    /* If no buffers are queued, playback is finished */
    alGetSourcei(pSource_, AL_BUFFERS_QUEUED, &queued);
    if (queued == 0)
      return;
    
    alSourcePlay(pSource_);
    if (alGetError() != AL_NO_ERROR)
      throw("Error restarting music playback");
  }
}

ALint MusicBuffer::get_source() {
  return pSource_;
}

MusicBuffer::MusicBuffer(const char* kFilename) {
  alGenSources(1, &pSource_);
  alGenBuffers(kNumBuffers_, pBuffers_);

  std::size_t frame_size;

  pSndFile_ = sf_open(kFilename, SFM_READ, &pSfInfo_);
  if (!pSndFile_)
    throw("Could not open provided music file -- check path");
  
  /* Get the sound format, and figure out the OpenAL format */
  if (pSfInfo_.channels == 1)
    pFormat_ = AL_FORMAT_MONO16;
  if (pSfInfo_.channels == 2) {
    pFormat_ = AL_FORMAT_STEREO16;
  } else if (pSfInfo_.channels ==3) {
    if (sf_command(pSndFile_, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == 
        SF_AMBISONIC_B_FORMAT)
      pFormat_ = AL_FORMAT_BFORMAT2D_16;
  } else if (pSfInfo_.channels == 4) {
    if (sf_command(pSndFile_, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == 
        SF_AMBISONIC_B_FORMAT)
      pFormat_ = AL_FORMAT_BFORMAT3D_16;
  }
  if (!pFormat_) {
    sf_close(pSndFile_);
    pSndFile_ = NULL;
    throw("Unsupported channel count from file");
  }

  frame_size = ((size_t)kBufferSamples_ 
              * (size_t)pSfInfo_.channels * sizeof(short));
  pMembuf_ = static_cast<short*>(malloc(frame_size));
}

MusicBuffer::~MusicBuffer() {
  alDeleteSources(1, &pSource_);

  if (pSndFile_)
    sf_close(pSndFile_);

  pSndFile_ = nullptr;

  free(pMembuf_);

  alDeleteBuffers(kNumBuffers_, pBuffers_);
}