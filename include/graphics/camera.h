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

#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
  kForward,
  kBackward,
  kLeft,
  kRight
};

// Default camera values
const float kYaw         = -90.0f;
const float kPitch       =  0.0f;
const float kSpeed       =  2.5f;
const float kSensitivity =  0.1f;
const float kZoom        =  90.0f;



// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera{
  public:
    // camera Attributes
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;
    // euler Angles
    float yaw_;
    float pitch_;
    // camera options
    float movement_speed_;
    float mouse_sensitivity_;
    float zoom_;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f), 
          glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw,
          float pitch = kPitch);
    // constructor with scalar values
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, 
          float up_z, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
      { return glm::lookAt(position_, position_ + front_, up_); }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraMovement direction, bool sprinting,
                        float delta_time);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float x_offset, float y_offset, 
                              GLboolean constrain_pitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float y_offset);

  private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors();
};

#endif