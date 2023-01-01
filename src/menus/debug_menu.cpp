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

#include <menus/debug_menu.h>

#include <cmath>

#include <imgui.h>

#include <version.h>

#define CPP_V11 201103L
#define CPP_V14 201402L
#define CPP_V17 201703L
#define CPP_V20 202002L

DebugMenu::DebugMenu(GLFWwindow* pWindow) {
  engine_version_ = std::to_string(ENGINE_VERSION_MAJOR) + "."
                  + std::to_string(ENGINE_VERSION_MINOR) + "."
                  + std::to_string(ENGINE_VERSION_PATCH);

#if __cplusplus == CPP_V11
  cpp_version_="11";
#elif __cplusplus == CPP_V14
  cpp_version_="14";
#elif __cplusplus == CPP_V17
  cpp_version_="17";
#elif __cplusplus == CPP_V20
  cpp_version_="20";
#else
  cpp_version_="";
#endif
  glfwMakeContextCurrent(pWindow);
  gl_version_=(char*)glGetString(GL_VERSION);

  gpu_vendor_ = gpu_.vendor();
  gpu_name_ = gpu_.name();
  
  cpu_cores_ = cpu_.numLogicalCores();
  cpu_model_name_ = cpu_.modelName();
}

void DebugMenu::Render(glm::vec2 text_pos, glm::vec3 pos, int fps) {
  ImGui::Begin("Debug Menu", NULL,
    ImGuiWindowFlags_NoDocking |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoScrollWithMouse |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoBackground |
    ImGuiWindowFlags_NoSavedSettings |
    ImGuiWindowFlags_NoFocusOnAppearing |
    ImGuiWindowFlags_NoNavInputs |
    ImGuiWindowFlags_NoNavFocus
  );
  ImGui::SetWindowPos(ImVec2(text_pos.x, text_pos.y));
  ImGui::SetWindowSize(ImVec2(428, 256));

  ImGui::Text("3D Engine %s (%s/vanilla/%s)", engine_version_.c_str(), 
                                              engine_version_.c_str(), 
                                              ENGINE_VERSION_PHASE);
  ImGui::Text("%d FPS", fps);
  ImGui::Text("Position: %.3f %.3f %.3f", pos.x, pos.y, pos.z);

  ImGui::Text("\nC++%s 64bit", cpp_version_.c_str());
  ImGui::Text("Lua %s.%s", LUA_VERSION_MAJOR, LUA_VERSION_MINOR);

  ImGui::Text("\nCPU: %dx %s", cpu_cores_, cpu_model_name_.c_str());

  const GLFWvidmode* pMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  ImGui::Text("\nDisplay %dx%d (%s)", pMode->width, pMode->height,
                                      gpu_vendor_.c_str());
  ImGui::Text("OpenGL %s", gl_version_.c_str());
  ImGui::Text("%s", gpu_name_.c_str());
  

  ImGui::Text("\nDebug: enabled (press F3 to toggle)");
  ImGui::Text("Press F1 for help.");
  ImGui::End();
}