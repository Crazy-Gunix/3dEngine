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

#ifndef CHEATMENU_H
#define CHEATMENU_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/camera.h>
#include <utils/object_manager.h>

class CheatMenu {
  public:
    void Render(GLFWwindow* pWindow, Camera& camera, 
                ObjectManager* object_manager,
                bool& cheat_menu, bool& paused);
  private:
    char tp_buf_x_[8] = "0";
    char tp_buf_y_[8] = "0";
    char tp_buf_z_[8] = "0";

    char obj_buf_x_[8] = "0";
    char obj_buf_y_[8] = "0";
    char obj_buf_z_[8] = "0";
};

#endif