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