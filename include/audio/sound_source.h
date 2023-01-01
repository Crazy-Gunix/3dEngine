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