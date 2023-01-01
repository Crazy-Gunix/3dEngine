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

#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include <AL/al.h>

class SoundSource {
  public:
    SoundSource();
    ~SoundSource();

    void Play(const ALuint kBuffer);
  private:
    ALuint pSource_;
    float pPitch_ = 1.0f;
    float pGain_ = 1.0f;
    float pPosition_[3] = { 0, 0, 0 };
    float pVelocity_[3] = { 0, 0, 0 };
    bool pLoopSound_ = false;
    ALuint pBuffer_ = 0;
};

#endif