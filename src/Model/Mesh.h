#pragma once

#include <glad/gl.h>

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader/Shader.h"
#include "Shader/VertexArray.h"
#include "Shader/ElementBuffer.h"
#include "Shader/VertexArray.h"

#include <string>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

struct Texture {
  uint32_t id;
  std::string type;
  std::string path;
};

class Mesh {
private:
  // uint32_t m_vbo;
  // uint32_t m_ebo;
  // uint32_t m_vao;
  sim3D::VertexBuffer m_vbo;
  sim3D::ElementBuffer m_ebo;
  sim3D::VertexArray m_vao;
  std::vector<Vertex> m_vertices;
  std::vector<uint32_t> m_indicies;
  std::vector<Texture> m_textures;
  uint32_t m_instances = 1;
  auto SetupMesh() -> void;

public:
  Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indicies, std::vector<Texture> textures); //, uint32_t instances);
  auto Draw(Shader& shader) -> void;
  auto AddVBO(const sim3D::VertexBuffer& vbo, const sim3D::VertexBufferLayout& layout, const uint32_t index = 0) const -> void;
  auto SetDivisor(uint32_t index, uint32_t divisor) const -> void;
  auto SetInstances(uint32_t instances) -> void { m_instances = instances; }
  auto BindVAO() -> void;
};
