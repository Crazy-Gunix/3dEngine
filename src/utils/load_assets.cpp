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

#include <utils/load_assets.h>

#include <iostream>

#include <stb_image.h>

#include <graphics/model.h>

bool LoadTextureFromFile(const char* kFilename, GLuint* pOutTexture,
                         int* pOutWidth, int* pOutHeight) {
  // Load from file
  int image_width = 0;
  int image_height = 0;

  std::cout << "Loading image \"" << kFilename << "\".\n";

  unsigned char* pImageData = stbi_load(kFilename,
                                        &image_width, &image_height,
                                        NULL, 4);
  if (pImageData == NULL)
    return false;

  // Create a OpenGL texture identifier
  GLuint image_texture;
  glGenTextures(1, &image_texture);
  glBindTexture(GL_TEXTURE_2D, image_texture);

  // Setup filtering parameters for display
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

  // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, pImageData);
  stbi_image_free(pImageData);

  *pOutTexture = image_texture;
  *pOutWidth = image_width;
  *pOutHeight = image_height;

  return true;
}

void LoadModels(GLFWwindow* pWindow, Model models[6], Model& square_model,
                bool& loading_ready, bool& loading_finished,
                std::string path) {
  while (!loading_ready); // Wait until the splash screen is displayed.
  glfwMakeContextCurrent(pWindow);
  stbi_set_flip_vertically_on_load(true);
  models[0].LoadModel(path + "/assets/objects/backpack/backpack.obj");
  stbi_set_flip_vertically_on_load(false);
  models[1].LoadModel(path + "/assets/objects/umbrella/umbrella.obj");
  models[2].LoadModel(path + "/assets/objects/coffee_cup/coffee_cup.obj");
  models[3].LoadModel(path + "/assets/objects/banana/banana.obj");
  models[4].LoadModel(path + "/assets/objects/nokia/nokia.obj");
  models[5].LoadModel(path + "/assets/objects/croissant/croissant.obj");
  square_model.LoadModel(path + "/assets/objects/plane/plane.obj");
  loading_finished = true;
}