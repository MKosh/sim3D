#pragma once

#include <cstdint>
#include <array>
#include <glm/fwd.hpp>
#include <vector>
#include "Renderer/Shader.h"
// #include "Simulation/Entity.h"
// #include "Simulation/Component.h"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ECS.h"

namespace sim3D{

// using Entity = std::uint32_t;

// World (box) that constrains the simulation
class World {
public:
  World(const uint32_t x, const uint32_t y, const uint32_t z) :
        m_x{x}, m_y{y}, m_z{z} {
    SetupWorld();
  }
  World();
  auto Draw(const glm::mat4& pv_matrix) -> void;
  auto SetupScene() -> void;
private:
  uint32_t m_x;
  uint32_t m_y;
  uint32_t m_z;
  uint32_t m_vao;
  uint32_t m_vbo;
  std::array<float, 72> m_vertices;
  Shader m_line_shader{"data/shaders/line.vert", "data/shaders/line.frag"};
  glm::mat4 m_model{1.0f};
  auto SetupWorld() -> void;
  Scene scene;

};


class Simulation {
public:
  Simulation();
  ~Simulation();

  auto Step(float dt) -> void;
  auto IsRunnning() -> bool;
  auto SetDeltaTime(float) -> void;
  auto Draw(const glm::mat4& pv_matrix) -> void;


private:
  bool m_running;
  float m_dt;
  World m_world;

};

}
