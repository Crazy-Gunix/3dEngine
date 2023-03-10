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

#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <graphics/window.h>

class LoadingScreen{
  public:
    LoadingScreen(std::string path);

    void Render(GLFWimage* image, Window& window, ImGuiIO& imgui_io,
                bool& loading_ready, bool& loading_finished,
                const int kScrWidth, const int kScrHeight,
                std::string message);
  private:
    std::string path_;
};

#endif