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

#ifndef MUSICBUFFER_H
#define MUSICBUFFER_H

#include <AL/al.h>
#include <sndfile.h>

class MusicBuffer {
  public:
    void Play();
    // void Pause();
    // void Stop();

    void UpdateBufferStream();

    ALint get_source();

    MusicBuffer(const char* kFilename);
    ~MusicBuffer();
  private:
    ALuint pSource_;
    static const int kBufferSamples_ = 8192;
    static const int kNumBuffers_ = 4;
    ALuint pBuffers_[kNumBuffers_];
    SNDFILE* pSndFile_;
    SF_INFO pSfInfo_;
    short* pMembuf_;
    ALenum pFormat_;

    MusicBuffer() = delete;
};

#endif