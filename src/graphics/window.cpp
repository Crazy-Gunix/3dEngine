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

#include <graphics/window.h>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}



Window::Window(const int width, const int height,
               std::string title) : title_(title),
               width_(width), height_(height) {
  if (!glfwInit())
    throw("Failed to initialize GLFW.");
  
  InitOpenGL();
}

Window::~Window() {
  Close(); // Close window if not already closed;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

void Window::set_title(std::string title) {
  title_ = title;
  glfwSetWindowTitle(window_, title_.c_str());
}

void Window::set_key_callback(void (*key_callback)(GLFWwindow*, int, int, int, int)) {
  glfwSetKeyCallback(window_, key_callback);
}

void Window::set_cursor_pos_callback(void (*cursor_pos_callback)
                                (GLFWwindow*, double, double)) {
  glfwSetCursorPosCallback(window_, cursor_pos_callback);
}

void Window::UpdateDelta() {
  float current_frame = static_cast<float>(glfwGetTime());
  delta_time_ = current_frame - last_frame_;
  last_frame_ = current_frame;
}

void Window::Clear(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Render() {
  glfwSwapBuffers(window_);
}

void Window::InitOpenGL() {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (window_ == NULL)
    throw("Failed to initialize GLFW window.");

  GLMakeContextCurrent();
  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw("Failed to initialize GLAD.");
}