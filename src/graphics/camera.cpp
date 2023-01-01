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

#include <graphics/camera.h>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
              front_(glm::vec3(0.f, 0.f, -1.f)), movement_speed_(kSpeed), 
              mouse_sensitivity_(kSensitivity), zoom_(kZoom) {
  position_ = position;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  UpdateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
                float up_z, float yaw, float pitch) : 
                front_(glm::vec3(0.f, 0.f, -1.f)), movement_speed_(kSpeed), 
                mouse_sensitivity_(kSensitivity), zoom_(kZoom) {
  position_ = glm::vec3(pos_x, pos_y, pos_z);
  world_up_ = glm::vec3(up_x, up_y, up_z);
  yaw_ = yaw;
  pitch_ = pitch;
  UpdateCameraVectors();
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(CameraMovement direction, bool sprinting, 
                            float delta_time) {
  int speed_boost = (sprinting) ? 2 : 1;
  float velocity = movement_speed_ * speed_boost * delta_time;
  if (direction == kForward) position_ += front_ * velocity;
  if (direction == kBackward) position_ -= front_ * velocity;
  if (direction == kLeft) position_ -= right_ * velocity;
  if (direction == kRight) position_ += right_ * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float x_offset, float y_offset, 
                                  GLboolean constrain_pitch) {
  x_offset *= ((zoom_==90) ? mouse_sensitivity_ : mouse_sensitivity_/4);
  y_offset *= ((zoom_==90) ? mouse_sensitivity_ : mouse_sensitivity_/4);

  yaw_   += x_offset;
  pitch_ += y_offset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrain_pitch) {
    if (pitch_ > 89.f) pitch_ = 89.f;
    if (pitch_ < -89.f) pitch_ = -89.f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  UpdateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) {
  zoom_ -= (float)yoffset;
  if (zoom_ < 1.f) zoom_ = 1.f;
  if (zoom_ > 45.f) zoom_ = 45.f;
}

void Camera::UpdateCameraVectors() {
  // calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front.y = sin(glm::radians(pitch_));
  front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_ = glm::normalize(front);
  // also re-calculate the right and up vector
  right_ = glm::normalize(glm::cross(front_, world_up_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  up_ = glm::normalize(glm::cross(right_, front_));
}