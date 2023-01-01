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