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
    void set_vec_4(const std::string& kName, float x, float y, float z, float w) const { 
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