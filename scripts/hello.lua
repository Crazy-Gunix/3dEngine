-- Copyright 2022 Jacob Gibson

-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at

--     http:--www.apache.org/licenses/LICENSE-2.0

-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

function Start()
  -- Runs on start.
  print("Hello from lua!")

  object = CreateObject();
  
  SetObjectType(object, OBJECT_TYPE_BACKPACK)
  SetObjectPosition(object, -4.0, 0.9, 0.0)
  SetObjectScale(object, 0.5, 0.5, 0.5);
  SpawnObject(object);

  SetObjectType(object, OBJECT_TYPE_UMBRELLA)
  SetObjectPosition(object, -2.0, 0.0, 0.0)
  SetObjectScale(object, 0.01, 0.01, 0.01)
  SpawnObject(object)

  SetObjectType(object, OBJECT_TYPE_COFFEE_CUP)
  SetObjectPosition(object, 0.0, 0.0, 0.0)
  SetObjectScale(object, 1.0, 1.0, 1.0)
  SpawnObject(object);

  SetObjectType(object, OBJECT_TYPE_BANANA)
  SetObjectPosition(object, 2.0, 0.1, 0.0)
  SetObjectScale(object, 1.0, 1.0, 1.0)
  SpawnObject(object)
  
  SetObjectType(object, OBJECT_TYPE_NOKIA)
  SetObjectPosition(object, 4.0, 0.35, 0.0)
  SetObjectScale(object, 0.15, 0.15, 0.15)
  SpawnObject(object);

  SetObjectType(object, OBJECT_TYPE_CROISSANT)
  SetObjectPosition(object, -12.5, 0.0, 25.0)
  SetObjectRotation(object, 0.0, -90.0, 0.0)
  SetObjectScale(object, 100.0, 100.0, 100.0)
  SpawnObject(object)
end

function Update(delta_time)
  -- Runs each frame.
end