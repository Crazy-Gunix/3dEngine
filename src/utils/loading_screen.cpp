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

#include <utils/loading_screen.h>

#include <iostream>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>

#include <misc/clear.h>
#include <utils/load_assets.h>

LoadingScreen::LoadingScreen(GLFWwindow* pWindow, std::string path) {
  pWindow_ = pWindow;
  path_ = path;
}

void LoadingScreen::Render(GLFWimage* image, ImGuiIO& imgui_io, bool& loading_ready, bool& loading_finished, const int kScrWidth, const int kScrHeight, std::string message) {
  for (int i = 0; i < 2; i++) {
    glfwSetInputMode(pWindow_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    ClearScreen(0.1f, 0.15f, 0.15f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();



    int window_x, window_y;
    glfwGetWindowPos(pWindow_, &window_x, &window_y);

    std::string img_path = path_ + "/assets/textures/awesomeface.png";

    int my_image_width = 0;
    int my_image_height= 0;
    GLuint my_image_texture = 0;
    stbi_set_flip_vertically_on_load(false);
    std::cout << "Loading image \"" << img_path << "\".\n";
    bool ret = LoadTextureFromFile(img_path.c_str(), &my_image_texture,
                                   &my_image_width, &my_image_height);
    stbi_set_flip_vertically_on_load(true);
    IM_ASSERT(ret);
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
    ImGui::SetWindowPos(ImVec2(
      window_x + (kScrWidth / 2 - my_image_width / 2),
      window_y + (kScrHeight / 2 - my_image_height / 2)
    ));
    
    ImGui::Image((void*)(intptr_t)my_image_texture,
                 ImVec2(my_image_width, my_image_height));

    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - ImGui::CalcTextSize(message.c_str()).x) * 0.5f;
    if (off > 0.0f)
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    
    ImGui::Text("%s",message.c_str());

    ImGui::End();



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* pBackupCurrentContext = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(pBackupCurrentContext);
    }
    glfwSetWindowIcon(pWindow_, 1, image);

    glfwMakeContextCurrent(pWindow_);
    glfwSwapBuffers(pWindow_);
    glfwPollEvents();
  }
  loading_ready = true;
  while (!loading_finished); // Wait until models finish loading.
}