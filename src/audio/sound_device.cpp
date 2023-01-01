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

#include <audio/sound_device.h>

#include <stdio.h>

#include <AL/al.h>

SoundDevice* SoundDevice::get() {
  static SoundDevice* pSndDevice = new SoundDevice();
  return pSndDevice;
}

SoundDevice::SoundDevice() {
  pALCDevice_ = alcOpenDevice(nullptr); // nullptr = get default device
  if (!pALCDevice_)
    throw("failed to get sound device");

  pALCContext_ = alcCreateContext(pALCDevice_, nullptr);  // create context
  if (!pALCContext_)
    throw("Failed to set sound context");

  if (!alcMakeContextCurrent(pALCContext_))   // make context current
    throw("failed to make context current");

  const ALCchar* pName = nullptr;
  if (alcIsExtensionPresent(pALCDevice_, "ALC_ENUMERATE_ALL_EXT"))
    pName = alcGetString(pALCDevice_, ALC_ALL_DEVICES_SPECIFIER);
  if (!pName || alcGetError(pALCDevice_) != AL_NO_ERROR)
    pName = alcGetString(pALCDevice_, ALC_DEVICE_SPECIFIER);
  printf("Opened \"%s\"\n", pName);
}

SoundDevice::~SoundDevice() {
  if (!alcMakeContextCurrent(nullptr))
    throw("failed to set context to nullptr");

  alcDestroyContext(pALCContext_);
  if (pALCContext_)
    throw("failed to unset during close");

  if (!alcCloseDevice(pALCDevice_))
    throw("failed to close sound device");
}