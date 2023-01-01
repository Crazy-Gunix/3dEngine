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

#include <graphics/shader.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* kVertexPath, const char* kFragmentPath) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;
  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

std::cout << "Loading shaders (vert: " << kVertexPath
            << ", frag: " << kFragmentPath << ").\n";

  try {
    // open files
    v_shader_file.open(kVertexPath);
    f_shader_file.open(kFragmentPath);
    std::stringstream v_shader_stream, f_shader_stream;
    // read file's buffer contents into streams
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code   = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
  } catch (std::ifstream::failure& e) {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: "
              << e.what() << '\n';
  }
  const char* kVShaderCode = vertex_code.c_str();
  const char * kFShaderCode = fragment_code.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &kVShaderCode, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &kFShaderCode, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");
  // shader Program
  id_ = glCreateProgram();
  glAttachShader(id_, vertex);
  glAttachShader(id_, fragment);
  glLinkProgram(id_);
  CheckCompileErrors(id_, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: "
          << type << "\n" << infoLog
          << "\n -- --------------------------------------------------- -- \n";
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: "
          << type << "\n" << infoLog
          << "\n -- --------------------------------------------------- -- \n";
    }
  }
}