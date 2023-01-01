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

#ifndef DEBUGMENU_H
#define DEBUGMENU_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <hwinfo/hwinfo.h>
extern "C" {
  #include <lua-5.4.4/include/lua.h>
  #include <lua-5.4.4/include/lauxlib.h>
  #include <lua-5.4.4/include/lualib.h>
}

class DebugMenu {
  public:
    DebugMenu(GLFWwindow* pWindow);

    void Render(glm::vec2 text_pos, glm::vec3 pos, int fps);
  private:
    std::string engine_version_;

    hwinfo::CPU cpu_;
    hwinfo::GPU gpu_;

    std::string cpp_version_;
    std::string gl_version_;

    std::string gpu_vendor_;
    std::string gpu_name_;

    std::string cpu_model_name_;
    int cpu_cores_;
};

#endif