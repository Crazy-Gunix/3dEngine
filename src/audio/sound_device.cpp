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