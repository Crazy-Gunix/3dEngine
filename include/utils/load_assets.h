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

#ifndef LOAD_ASSETS_H
#define LOAD_ASSETS_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/model.h>

bool LoadTextureFromFile(const char* kFilename, GLuint* pOutTexture,
                         int* pOutWidth, int* pOutHeight);

void LoadModels(GLFWwindow* pWindow, Model models[6], Model& square_model,
                bool& loading_ready, bool& loading_finished, std::string path);

#endif