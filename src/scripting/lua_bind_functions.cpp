/*
Copyright (C) 2022 Jacob Gibson

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

#include <scripting/lua_bind_functions.h>

#include <iostream>

struct LuaObject {
  int type;

  float position_x;
  float position_y;
  float position_z;

  float rotation_x;
  float rotation_y;
  float rotation_z;

  float scale_x;
  float scale_y;
  float scale_z;
};


ObjectManager* obj_manager;

int LuaCreateObject(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_newuserdata(L, sizeof(LuaObject));
  object->type = kObjectTypeBanana;
  object->position_x = 0.0f;
  object->position_y = 0.0f;
  object->position_z = 0.0f;

  object->rotation_x = 0.0f;
  object->rotation_y = 0.0f;
  object->rotation_z = 0.0f;

  object->scale_x = 1.0f;
  object->scale_y = 1.0f;
  object->scale_z = 1.0f;

  return 1;
}

int LuaSpawnObject(lua_State* L) {
  std::cout << "Spawning object from Lua.\n";
  LuaObject* object = (LuaObject*)lua_touserdata(L, -1);

  Object obj;
  obj.type = (ObjectType)object->type;
  obj.position = glm::vec3(object->position_x,
                         object->position_y,
                         object->position_z
  );
  obj.rotation = glm::vec3(object->rotation_x,
                         object->rotation_y,
                         object->rotation_z
  );
  obj.scale = glm::vec3(object->scale_x,
                         object->scale_y,
                         object->scale_z
  );

  obj_manager->AddObject(obj);

  return 0;
}

int lua_get_object_type(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -1);
  lua_pushnumber(L, object->type);
  return 1;
}
int lua_set_object_type(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -2);
  object->type = (int)lua_tonumber(L, -1);
  return 0;
}

int lua_get_object_position(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -1);
  lua_pushnumber(L, object->position_x);
  lua_pushnumber(L, object->position_y);
  lua_pushnumber(L, object->position_z);
  return 3;
}
int lua_set_object_position(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -4);
  object->position_x = (float)lua_tonumber(L, -3);
  object->position_y = (float)lua_tonumber(L, -2);
  object->position_z = (float)lua_tonumber(L, -1);
  return 0;
}

int lua_get_object_rotation(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -1);
  lua_pushnumber(L, object->rotation_x);
  lua_pushnumber(L, object->rotation_y);
  lua_pushnumber(L, object->rotation_z);
  return 3;
}
int lua_set_object_rotation(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -4);
  object->rotation_x = (float)lua_tonumber(L, -3);
  object->rotation_y = (float)lua_tonumber(L, -2);
  object->rotation_z = (float)lua_tonumber(L, -1);
  return 0;
}

int lua_get_object_scale(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -1);
  lua_pushnumber(L, object->scale_x);
  lua_pushnumber(L, object->scale_y);
  lua_pushnumber(L, object->scale_z);
  return 3;
}
int lua_set_object_scale(lua_State* L) {
  LuaObject* object = (LuaObject*)lua_touserdata(L, -4);
  object->scale_x = (float)lua_tonumber(L, -3);
  object->scale_y = (float)lua_tonumber(L, -2);
  object->scale_z = (float)lua_tonumber(L, -1);
  return 0;
}

void LuaBindFunctions(lua_State* L, ObjectManager* object_manager) {
  obj_manager=object_manager;

  lua_pushcfunction(L, LuaCreateObject);
  lua_setglobal(L, "CreateObject");
  lua_pushcfunction(L, LuaSpawnObject);
  lua_setglobal(L, "SpawnObject");

  lua_pushcfunction(L, lua_get_object_type);
  lua_setglobal(L, "GetObjectType");
  lua_pushcfunction(L, lua_set_object_type);
  lua_setglobal(L, "SetObjectType");

  lua_pushcfunction(L, lua_get_object_position);
  lua_setglobal(L, "GetObjectPosition");
  lua_pushcfunction(L, lua_set_object_position);
  lua_setglobal(L, "SetObjectPosition");

  lua_pushcfunction(L, lua_get_object_rotation);
  lua_setglobal(L, "GetObjectRotation");
  lua_pushcfunction(L, lua_set_object_rotation);
  lua_setglobal(L, "SetObjectRotation");

  lua_pushcfunction(L, lua_get_object_scale);
  lua_setglobal(L, "GetObjectScale");
  lua_pushcfunction(L, lua_set_object_scale);
  lua_setglobal(L, "SetObjectScale");

  lua_pushnumber(L, kObjectTypeBackpack);
  lua_setglobal(L, "OBJECT_TYPE_BACKPACK");
  lua_pushnumber(L, kObjectTypeUmbrella);
  lua_setglobal(L, "OBJECT_TYPE_UMBRELLA");
  lua_pushnumber(L, kObjectTypeCoffeeCup);
  lua_setglobal(L, "OBJECT_TYPE_COFFEE_CUP");
  lua_pushnumber(L, kObjectTypeBanana);
  lua_setglobal(L, "OBJECT_TYPE_BANANA");
  lua_pushnumber(L, kObjectTypeNokia);
  lua_setglobal(L, "OBJECT_TYPE_NOKIA");
  lua_pushnumber(L, kObjectTypeCroissant);
  lua_setglobal(L, "OBJECT_TYPE_CROISSANT");
}