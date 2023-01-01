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

#include <menus/help_menu.h>

#include <imgui.h>

void HelpMenu::Render(GLFWwindow* pWindow, bool& help_menu,
                      const int kScrWidth, int kScrHeight) {
  int window_x, window_y;
  glfwGetWindowPos(pWindow, &window_x, &window_y);

  ImVec2 center = ImVec2(window_x+kScrWidth/2, window_y+kScrHeight/2);
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  ImGui::OpenPopup("Debug Help");
  if (ImGui::BeginPopupModal("Debug Help", NULL,
                             ImGuiWindowFlags_AlwaysAutoResize |
                             ImGuiWindowFlags_NoSavedSettings | 
                             ImGuiWindowFlags_NoMove)) {
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    ImGui::SetItemDefaultFocus();
    ImGui::Text("F1 - Help Menu");
    ImGui::Text("F3 - Toggle Debug Screen");
    ImGui::Text("F8 - Toggle Wireframe Mode\n\n");

    ImGui::Separator();

    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - ImGui::CalcTextSize("OK").x) * 0.5f;
    if (off > 0.0f)
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    if (ImGui::Button("OK")) {
      ImGui::CloseCurrentPopup();
      help_menu=false;
      glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    ImGui::EndPopup();
  }
}