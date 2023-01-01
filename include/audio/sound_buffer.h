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

#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include <vector>

#include <AL/al.h>

class SoundBuffer {
  public:
    static SoundBuffer* get();

    ALuint AddSoundEffect(const char* kFilename);
    bool RemoveSoundEffect(const ALuint& kBuffer);
  private:
    SoundBuffer();
    ~SoundBuffer();

    std::vector<ALuint> pSoundEffectBuffers_;
};

#endif