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