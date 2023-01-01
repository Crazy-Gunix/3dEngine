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

#include <menus/cheat_menu.h>

#include <stdexcept>
#include <string>
#include <iostream>

#include <imgui.h>

void CheatMenu::Render(GLFWwindow* pWindow, Camera& camera,
                       ObjectManager* object_manager,
                       bool& cheat_menu, bool& paused) {
  ImGui::Begin("Cheat Menu",NULL,ImGuiWindowFlags_NoSavedSettings);
  ImGui::SetWindowSize(ImVec2(384,256));
  ImGui::SliderFloat("Movement Speed", &camera.movement_speed_, 0.0f, 20.0f);

  ImGui::Separator();
  ImGui::InputText("Tp X", tp_buf_x_, IM_ARRAYSIZE(tp_buf_x_));
  ImGui::InputText("Tp Y", tp_buf_y_, IM_ARRAYSIZE(tp_buf_y_));
  ImGui::InputText("Tp Z", tp_buf_z_, IM_ARRAYSIZE(tp_buf_z_));
  if (ImGui::Button("Teleport")) {
    try {
      float x=std::stof(tp_buf_x_);
      float y=std::stof(tp_buf_y_);
      float z=std::stof(tp_buf_z_);
      camera.position_=glm::vec3(x, y, z);
      paused=false;
      glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      std::cout << "Teleported player to: ("
                << x << ", " << y << ", " << z << ")\n";
    } catch(std::invalid_argument) {
      std::cerr<<"ERROR: Invalid position provided.\n";
    }
  }

  ImGui::Separator();
  ImGui::InputText("Object X", obj_buf_x_, IM_ARRAYSIZE(obj_buf_x_));
  ImGui::InputText("Object Y", obj_buf_y_, IM_ARRAYSIZE(obj_buf_y_));
  ImGui::InputText("Object Z", obj_buf_z_, IM_ARRAYSIZE(obj_buf_z_));

  const char* kItems[] = {
    "Backpack",
    "Umbrella",
    "Coffee Cup",
    "Banana",
    "Nokia",
    "Croissant"
  };
  static const char* kCurrentItem = "Backpack";

  if (ImGui::BeginCombo("##combo", kCurrentItem)) {
    for (int n = 0; n < IM_ARRAYSIZE(kItems); n++) {
      bool is_selected = (kCurrentItem == kItems[n]);
      if (ImGui::Selectable(kItems[n], is_selected))
        kCurrentItem = kItems[n];
      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }


  ImGui::SameLine();
  if (ImGui::Button("Spawn Object")) {
    std::cout << "Spawning \"" << kCurrentItem << "\".\n";

    float x = std::stof(obj_buf_x_);
    float y = std::stof(obj_buf_y_);
    float z = std::stof(obj_buf_z_);

    Object obj;
    obj.position = glm::vec3(x, y, z);

    bool error = false;

    if (kCurrentItem == "Backpack") {
      obj.type=kObjectTypeBackpack;
      obj.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    } else if (kCurrentItem == "Umbrella") {
      obj.type=kObjectTypeUmbrella;
      obj.scale = glm::vec3(0.01f, 0.01f, 0.01f);
    } else if (kCurrentItem == "Coffee Cup") {
      obj.type=kObjectTypeCoffeeCup;
    } else if (kCurrentItem == "Banana") {
      obj.type=kObjectTypeBanana;
    } else if (kCurrentItem == "Nokia") {
      obj.type=kObjectTypeNokia;
      obj.scale = glm::vec3(0.15f, 0.15f, 0.15f);
    } else if (kCurrentItem == "Croissant") {
      obj.type=kObjectTypeCroissant;
      obj.rotation = glm::vec3(0.0f, -90.0f, 0.0f);
    } else {
      std::cerr << "Error spawning object.\n";
      error=true;
    }

    if (!error) {
      object_manager->AddObject(obj);
    }
  }

}