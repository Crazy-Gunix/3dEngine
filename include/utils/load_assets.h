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

#ifndef LOAD_ASSETS_H
#define LOAD_ASSETS_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/model.h>

bool LoadTextureFromFile(const char* kFilename, GLuint* pOutTexture,
                         int* pOutWidth, int* pOutHeight);

void LoadModels(GLFWwindow* pWindow, Model models[6], Model& square_model, bool& loading_ready, bool& loading_finished, std::string path);

#endif