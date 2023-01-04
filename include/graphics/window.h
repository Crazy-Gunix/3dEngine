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

#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Window {
  public:
    // Construct/Destruct
    Window(const int width, const int height, std::string title);
    ~Window();

    // Setters/Getters
    GLFWwindow* get_window() { return window_; }
    std::string get_title() { return title_; }
    float get_delta_time() { return delta_time_; }
    
    void set_title(std::string title);
    void set_key_callback(void (*key_callback)(GLFWwindow*, int, int, int, int));
    void set_cursor_pos_callback(void (*cursor_pos_callback)
                                (GLFWwindow*, double, double));

    bool IsOpen() { return !glfwWindowShouldClose(window_); }

    // OpenGL Related Functions
    void GLMakeContextCurrent() { glfwMakeContextCurrent(window_); }

    // Events
    void PollEvents() { glfwPollEvents(); }
    void Close() { glfwSetWindowShouldClose(window_, GLFW_TRUE); }
    void UpdateDelta();

    // Rendering
    void Clear(float r, float g, float b, float a = 1.0f);
    void Render();
  private:
    GLFWwindow* window_;
    std::string title_;
    const int width_, height_;
    float delta_time_;
    float last_frame_;

    void InitOpenGL();
};

#endif