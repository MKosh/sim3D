#pragma once

#include <glad/gl.h>
#include <SFML/System/Vector2.hpp>

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
  kForward,
  kBackward,
  kLeft,
  kRight,
  kUp,
  kDown
};

const float kYaw         = -90.0f;
const float kPitch       = 0.0f;
const float kSpeed       = 2.5f;
const float kSensitivity = 0.1f;
const float kZoom        = 45.0f;

class Camera {
public:

  Camera(glm::vec3 position = glm::vec3{0.0f, 0.0f, -3.0f}, glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f}, float yaw = kYaw, float pitch = kPitch);
  Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw = kYaw, float pitch = kPitch);

  auto GetViewMatrix() -> glm::mat4;

  auto ProcessMovement(CameraMovement direction, float delta_time) -> void;
  auto ProcessMouseMovement(sf::Vector2i new_pos, GLboolean constrain_pitch = true) -> void;
  auto ProcessMouseScroll(float y_offset) -> void;
  auto GetZoom() -> float { return m_zoom; }
  auto GetYaw() -> float { return m_yaw; }
  auto GetPitch() -> float { return m_pitch; }
  auto GetCurrentMouse() -> sf::Vector2i { return m_current_mouse; }
  auto GetLastMouse() -> sf::Vector2i { return m_last_mouse; }

  auto SetYaw(float new_yaw) -> void { m_yaw = new_yaw; UpdateCameraVectors(); }
  auto SetPitch(float new_pitch) -> void { m_pitch = new_pitch; UpdateCameraVectors(); }
  auto SetZoom(float new_zoom) -> void { m_zoom = new_zoom; UpdateCameraVectors(); }
  auto SetMousePos(sf::Vector2i pos) -> void { m_last_mouse = pos; m_current_mouse = pos; }

  auto ResetCamera() -> void;

private:
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_world_up;

  float m_yaw;
  float m_pitch;
  float m_movement_speed;
  float m_mouse_sens;
  float m_zoom;

  sf::Vector2i m_current_mouse;
  sf::Vector2i m_last_mouse;

  auto UpdateCameraVectors() -> void;
};
