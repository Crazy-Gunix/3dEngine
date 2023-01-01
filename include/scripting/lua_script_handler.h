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