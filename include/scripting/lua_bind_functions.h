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

#ifndef LUA_BIND_FUNCTIONS
#define LUA_BIND_FUNCTIONS

#include <vector>

extern "C" {
  #include <lua-5.4.4/include/lua.h>
  #include <lua-5.4.4/include/lauxlib.h>
  #include <lua-5.4.4/include/lualib.h>
}

#include <utils/object_manager.h>

void LuaBindFunctions(lua_State* L, ObjectManager* object_manager);

#endif