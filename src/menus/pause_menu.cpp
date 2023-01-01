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