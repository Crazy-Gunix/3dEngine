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

#include <utils/play_audio.h>

#include <iostream>
#include <thread>

#include <AL/al.h>

#include <audio/music_buffer.h>
#include <audio/sound_buffer.h>
#include <audio/sound_source.h>

void PlaySoundThread(uint32_t sound) {
  SoundSource speaker;
  speaker.Play(sound);
}

void PlayMusicThread(std::string path, bool loop = false) {
  if (!loop) {
    MusicBuffer music(path.c_str());
    music.Play();

    ALint state = AL_PLAYING;
    while (state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
      music.UpdateBufferStream();

      alGetSourcei(music.get_source(), AL_SOURCE_STATE, &state);
    }
    return;
  }
  while (true) {
    MusicBuffer music(path.c_str());
    music.Play();

    ALint state = AL_PLAYING;
    while(state == AL_PLAYING && alGetError() == AL_NO_ERROR){
      music.UpdateBufferStream();

      alGetSourcei(music.get_source(), AL_SOURCE_STATE, &state);
    }
  }
}



void PlaySound(std::string path) {
  uint32_t sound = SoundBuffer::get()->AddSoundEffect(path.c_str());
  std::cout<<"Playing sound: \"" << path << "\".\n";
  std::thread t(PlaySoundThread, sound);
  t.detach();
}

void PlayMusic(std::string path, bool loop) {
  std::cout<<"Playing music: \"" << path << "\".\n";
  std::thread t(PlayMusicThread, path, loop);
  t.detach();
}