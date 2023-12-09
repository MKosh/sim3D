#pragma once

/* #include <glad/gl.h> */

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader/Shader.h"

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
  uint32_t m_vao;
  uint32_t m_vbo;
  uint32_t m_ebo;
  uint32_t m_instances;
  std::vector<glm::mat4> m_instance_matrix;
  std::vector<Vertex> m_vertices;
  std::vector<uint32_t> m_indicies;
  std::vector<Texture> m_textures;
  auto SetupMesh() -> void;

public:
  Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indicies, std::vector<Texture> textures, uint32_t instances);
  auto Draw(Shader& shader) -> void;
};
