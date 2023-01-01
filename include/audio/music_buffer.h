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