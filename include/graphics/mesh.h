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

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <graphics/shader.h>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;

  glm::vec3 tangent;
  // bitangent
  glm::vec3 bitangent;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
  public:
    // mesh data
    std::vector<Vertex>      vertices_;
    std::vector<unsigned int>  indices_;
    std::vector<Texture>    textures_;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
        std::vector<Texture> textures);
    void Draw(Shader& shader);
  private:
    //  render data
    unsigned int vao_, vbo_, ebo_;

    void SetupMesh();
}; 

#endif