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

#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
  public:
    unsigned int id_;

    Shader(const char* kVertexPath, const char* kFragmentPath);

    void Use(){glUseProgram(id_);}

    void set_bool(const std::string& kName, bool value) const { 
      glUniform1i(glGetUniformLocation(id_, kName.c_str()), (int)value); }
    void set_int(const std::string& kName, int value) const { 
      glUniform1i(glGetUniformLocation(id_, kName.c_str()), value); }
    void set_float(const std::string& kName, float value) const { 
      glUniform1f(glGetUniformLocation(id_, kName.c_str()), value); }

    void set_vec_2(const std::string& kName, const glm::vec2 &kValue) const { 
      glUniform2fv(glGetUniformLocation(id_, kName.c_str()), 1, &kValue[0]); }
    void set_vec_2(const std::string& kName, float x, float y) const { 
      glUniform2f(glGetUniformLocation(id_, kName.c_str()), x, y); }

    void set_vec_3(const std::string& kName, const glm::vec3& kValue) const { 
      glUniform3fv(glGetUniformLocation(id_, kName.c_str()), 1, &kValue[0]); }
    void set_vec_3(const std::string& kName, float x, float y, float z) const {
      glUniform3f(glGetUniformLocation(id_, kName.c_str()), x, y, z); }

    void set_vec_4(const std::string& kName, const glm::vec4& kValue) const { 
      glUniform4fv(glGetUniformLocation(id_, kName.c_str()), 1, &kValue[0]); }
    void set_vec_4(const std::string& kName, float x, float y,
                   float z, float w) const { 
      glUniform4f(glGetUniformLocation(id_, kName.c_str()), x, y, z, w); }

    void set_mat_2(const std::string& kName, const glm::mat2 &kMat) const { 
      glUniformMatrix2fv(glGetUniformLocation(id_, kName.c_str()), 1, 
                        GL_FALSE, &kMat[0][0]); }
    void set_mat_3(const std::string& kName, const glm::mat3& kMat) const { 
      glUniformMatrix3fv(glGetUniformLocation(id_, kName.c_str()), 1, 
                        GL_FALSE, &kMat[0][0]); }
    void set_mat_4(const std::string& kName, const glm::mat4& kMat) const { 
      glUniformMatrix4fv(glGetUniformLocation(id_, kName.c_str()), 1, 
                        GL_FALSE, &kMat[0][0]); }
  private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif