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

#ifndef LUA_SCRIPT_HANDLER_H
#define LUA_SCRIPT_HANDLER_H

#include <string>
#include <vector>

extern "C" {
  #include <lua-5.4.4/include/lua.h>
  #include <lua-5.4.4/include/lauxlib.h>
  #include <lua-5.4.4/include/lualib.h>
}

#include <utils/object_manager.h>

struct LuaScript {
  std::string path;
  std::string code;
};

class LuaScriptHandler {
  public:
    LuaScriptHandler(ObjectManager* object_manager);

    void AddScript(std::string path);
    void RemoveScript(std::string path);

    void RunUpdateFuncs(float delta_time);
  private:
    std::vector<LuaScript> scripts_;
    lua_State* L_;

    void RunScriptInit(std::string code);
    void RunScriptUpdate(std::string code, float delta_time);

    bool ScriptExists(std::string path);
    int GetIndexOfScript(std::string path);
};

#endif