-- Copyright (C) 2023 Jacob Gibson
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <https://www.gnu.org/licenses/>.

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