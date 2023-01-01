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

#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class LoadingScreen{
  public:
    LoadingScreen(GLFWwindow* pWindow, std::string path);

    void Render(GLFWimage* image, ImGuiIO& imgui_io, bool& loading_ready, bool& loading_finished, const int kScrWidth, const int kScrHeight, std::string message);
  private:
    GLFWwindow* pWindow_;
    std::string path_;
};

#endif