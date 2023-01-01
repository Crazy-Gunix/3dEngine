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

#include <menus/pause_menu.h>

#include <imgui.h>

void PauseMenu::Render(GLFWwindow* pWindow, bool& paused,
                       const int kScrWidth, const int kScrHeight) {
  ImGui::Begin("Pause Menu", NULL,
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

  int window_x, window_y;
  glfwGetWindowPos(pWindow, &window_x, &window_y);

  ImGui::SetWindowPos(ImVec2(window_x+(kScrWidth/2)-160,
                             window_y+(kScrHeight/4)-32));

  ImGui::SetWindowFontScale(8.0);
  ImGui::Text("Paused");

  ImGui::SetWindowFontScale(1.0);
  if (ImGui::Button("Resume", ImVec2(320,64))) {
    paused=false;
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  if (ImGui::Button("Exit", ImVec2(320,64))) {
    glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
  }

  ImGui::End();
}