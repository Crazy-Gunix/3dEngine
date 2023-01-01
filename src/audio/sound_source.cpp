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

#include <audio/sound_source.h>

#include <iostream>

SoundSource::SoundSource() {
  alGenSources(1, &pSource_);
  alSourcef(pSource_, AL_PITCH, pPitch_);
  alSourcef(pSource_, AL_GAIN, pGain_);
  alSource3f(pSource_, AL_POSITION, 
             pPosition_[0], pPosition_[1], pPosition_[2]);
  alSource3f(pSource_, AL_VELOCITY,
             pVelocity_[0], pVelocity_[1], pVelocity_[2]);
  alSourcei(pSource_, AL_LOOPING, pLoopSound_);
  alSourcei(pSource_, AL_BUFFER, pBuffer_);
}

SoundSource::~SoundSource() {
  alDeleteSources(1, &pSource_);
}

void SoundSource::Play(const ALuint kBuffer) {
  if (kBuffer != pBuffer_) {
      pBuffer_ = kBuffer;
      alSourcei(pSource_, AL_BUFFER, (ALint)pBuffer_);
  }

  alSourcePlay(pSource_);


  ALint state = AL_PLAYING;
  while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    alGetSourcei(pSource_, AL_SOURCE_STATE, &state);
}