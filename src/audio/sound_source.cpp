// Copyright 2022 Jacob Gibson

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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