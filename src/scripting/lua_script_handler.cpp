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

#include <scripting/lua_script_handler.h>

#include <filesystem>
#include <iostream>
#include <fstream>

#include <scripting/lua_bind_functions.h>

bool CheckLua(lua_State* L, int result) {
  if (result != LUA_OK) {
    std::cerr << lua_tostring(L, -1) << '\n';
    return false;
  }
  return true;
}



LuaScriptHandler::LuaScriptHandler(ObjectManager* object_manager) {
  L_ = luaL_newstate();
  luaL_openlibs(L_);
  LuaBindFunctions(L_, object_manager);
}

void LuaScriptHandler::AddScript(std::string path) {
  if (!std::filesystem::exists(path)) {
    std::cerr << "Error: File does not exist.\n";
    return;
  }

  std::cout << "Loading Lua script \"" << path << "\".\n";

  std::ifstream ifs(path);
  std::string ln;
  LuaScript script;

  script.path = path;
  
  while (std::getline(ifs, ln)) {
    script.code += ln;
    script.code.push_back('\n');
  }
  ifs.close();

  scripts_.push_back(script);

  RunScriptInit(script.code);
}

void LuaScriptHandler::RemoveScript(std::string path) {
  if (!ScriptExists(path)) {
    std::cerr << "Error: Script does not exist.\n";
    return;
  }

  int i = GetIndexOfScript(path);
  if (i == -1) {
    std::cerr << "Error: Failed to delete script.\n";
    return;
  }

  scripts_.erase(scripts_.begin() + i);

  std::cout << "Successfully removed script.\n";
}

void LuaScriptHandler::RunUpdateFuncs(float delta_time) {
  for (LuaScript script : scripts_) {
    RunScriptUpdate(script.code, delta_time);
  }
}

void LuaScriptHandler::RunScriptInit(std::string code) {
  if (CheckLua(L_, luaL_dostring(L_, code.c_str()))) {
    lua_getglobal(L_, "Start");
    if (lua_isfunction(L_, -1)) {
      CheckLua(L_, lua_pcall(L_, 0, 0, 0));
    }
  }
}

void LuaScriptHandler::RunScriptUpdate(std::string code, float delta_time) {
  if (CheckLua(L_, luaL_dostring(L_, code.c_str()))) {
    lua_getglobal(L_, "Update");
    if (lua_isfunction(L_, -1)) {
      lua_pushnumber(L_, delta_time);
      CheckLua(L_, lua_pcall(L_, 1, 0, 0));
    }
  }
}

bool LuaScriptHandler::ScriptExists(std::string path) {
  for (LuaScript script : scripts_) {
    if (script.path == path)
      return true;
  }
  return false;
}

int LuaScriptHandler::GetIndexOfScript(std::string path) {
  int i = 0;
  bool found = false;
  for (LuaScript script : scripts_) {
    if (script.path == path) {
      found = true;
      break;
    }
    i++;
  }

  if (found)
    return i;
  return -1;
}