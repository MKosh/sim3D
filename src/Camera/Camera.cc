#include "Camera.h"

#include <iostream>
#include <glm/ext/quaternion_geometric.hpp>

namespace sim3D {

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    :m_position{position}, m_front{glm::vec3{0.0f, 0.0f, -1.0f}}, m_world_up{up}, m_yaw{yaw}, m_pitch{pitch}, m_movement_speed{kSpeed}, m_mouse_sens{kSensitivity}, m_zoom{kZoom} {
  UpdateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch) 
    : m_position{glm::vec3{pos_x, pos_y, pos_z}}, m_front{glm::vec3{0.0f, 0.0f, -1.0f}}, m_world_up{glm::vec3{up_x, up_y, up_z}}, m_yaw{yaw}, m_pitch{pitch}, m_movement_speed{kSpeed}, m_mouse_sens{kSensitivity}, m_zoom{kZoom} {
  UpdateCameraVectors();
}

auto Camera::GetViewMatrix() -> glm::mat4 {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

auto Camera::ProcessMovement(CameraMovement direction, float delta_time) -> void {
  float velocity = m_movement_speed * delta_time;
  if (direction == CameraMovement::kForward) {
    m_position += m_front * velocity;
  }
  if (direction == CameraMovement::kBackward) {
    m_position -= m_front * velocity;
  }
  if (direction == CameraMovement::kLeft) {
    m_position -= m_right * velocity;
  }
  if (direction == CameraMovement::kRight) {
    m_position += m_right * velocity;
  }
  if (direction == CameraMovement::kUp) {
    m_position += m_world_up * velocity;
  }
  if (direction == CameraMovement::kDown) {
    m_position -= m_world_up * velocity;
  }
}

/* auto Camera::ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch) -> void { */
auto Camera::ProcessMouseMovement(sim3D::Vec2<int> new_pos, bool constrain_pitch) -> void {
  m_current_mouse = new_pos;
  float x_offset = (m_current_mouse.x - m_last_mouse.x) * m_mouse_sens;
  float y_offset = (m_current_mouse.y - m_last_mouse.y) * m_mouse_sens;
  m_yaw += x_offset;
  m_pitch += y_offset;

  if (constrain_pitch) {
    if (m_pitch > 89.0f)
      m_pitch = 89.0f;
    if (m_pitch < -89.0f)
      m_pitch = -89.0f;
  }

  m_last_mouse = m_current_mouse;
  UpdateCameraVectors();
}


auto Camera::ProcessMouseScroll(float y_offset) -> void {
  m_zoom -= (float)y_offset;
  if (m_zoom < 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >45.0f)
    m_zoom = 45.0f;
}

auto Camera::UpdateCameraVectors() -> void {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = -sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

  m_front = glm::normalize(front);
  m_right = glm::normalize(glm::cross(m_front, m_world_up));
  m_up    = glm::normalize(glm::cross(m_right, m_front));
}

auto Camera::ResetCamera() -> void {
  m_position = glm::vec3{0.0f, 0.0f, -1.0f};
  m_yaw = -90.0f;
  m_pitch = 0.0f;

  UpdateCameraVectors();
}
}
