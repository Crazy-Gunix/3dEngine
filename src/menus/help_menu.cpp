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