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

#include <menus/cheat_menu.h>

#include <stdexcept>
#include <string>
#include <iostream>

#include <imgui.h>

void CheatMenu::Render(GLFWwindow* pWindow, Camera& camera,
                       ObjectManager* object_manager,
                       bool& cheat_menu, bool& paused) {
  ImGui::Begin("Cheat Menu",NULL,ImGuiWindowFlags_NoSavedSettings);
  ImGui::SetWindowSize(ImVec2(384, 320));
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
  ImGui::InputText("Position X", obj_buf_pos_x_, IM_ARRAYSIZE(obj_buf_pos_x_));
  ImGui::InputText("Position Y", obj_buf_pos_y_, IM_ARRAYSIZE(obj_buf_pos_y_));
  ImGui::InputText("Position Z", obj_buf_pos_z_, IM_ARRAYSIZE(obj_buf_pos_z_));
  ImGui::InputText("Rotation X", obj_buf_rot_x_, IM_ARRAYSIZE(obj_buf_rot_x_));
  ImGui::InputText("Rotation Y", obj_buf_rot_y_, IM_ARRAYSIZE(obj_buf_rot_y_));
  ImGui::InputText("Rotation Z", obj_buf_rot_z_, IM_ARRAYSIZE(obj_buf_rot_z_));
  ImGui::InputText("Scale X", obj_buf_scale_x_, IM_ARRAYSIZE(obj_buf_scale_x_));
  ImGui::InputText("Scale Y", obj_buf_scale_y_, IM_ARRAYSIZE(obj_buf_scale_y_));
  ImGui::InputText("Scale Z", obj_buf_scale_z_, IM_ARRAYSIZE(obj_buf_scale_z_));

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

    float pos_x = std::stof(obj_buf_pos_x_);
    float pos_y = std::stof(obj_buf_pos_y_);
    float pos_z = std::stof(obj_buf_pos_z_);

    float rot_x = std::stof(obj_buf_rot_x_);
    float rot_y = std::stof(obj_buf_rot_y_);
    float rot_z = std::stof(obj_buf_rot_z_);

    float scale_x = std::stof(obj_buf_scale_x_);
    float scale_y = std::stof(obj_buf_scale_y_);
    float scale_z = std::stof(obj_buf_scale_z_);

    Object obj;
    obj.position = glm::vec3(pos_x, pos_y, pos_z);
    obj.rotation = glm::vec3(rot_x, rot_y, rot_z);
    obj.scale = glm::vec3(scale_x, scale_y, scale_z);

    bool error = false;

    if (kCurrentItem == "Backpack") {
      obj.type=kObjectTypeBackpack;
      obj.scale *= glm::vec3(0.5f, 0.5f, 0.5f);
    } else if (kCurrentItem == "Umbrella") {
      obj.type=kObjectTypeUmbrella;
      obj.scale *= glm::vec3(0.01f, 0.01f, 0.01f);
    } else if (kCurrentItem == "Coffee Cup") {
      obj.type=kObjectTypeCoffeeCup;
    } else if (kCurrentItem == "Banana") {
      obj.type=kObjectTypeBanana;
    } else if (kCurrentItem == "Nokia") {
      obj.type=kObjectTypeNokia;
      obj.scale *= glm::vec3(0.15f, 0.15f, 0.15f);
    } else if (kCurrentItem == "Croissant") {
      obj.type=kObjectTypeCroissant;
      obj.rotation *= glm::vec3(0.0f, -90.0f, 0.0f);
    } else {
      std::cerr << "Error spawning object.\n";
      error=true;
    }

    if (!error) {
      object_manager->AddObject(obj);
    }
  }

}