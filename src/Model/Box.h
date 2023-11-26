#include <cstdint>
/* #include <glad/gl.h> */
#include <array>
#include <glm/glm.hpp>

class Box {
public:
  Box(uint32_t width, uint32_t height, uint32_t depth)
    : m_width{width}, m_height{height}, m_depth{depth} { SetupBox(); }

  Box() { SetupBox(); }
  auto Draw() -> void;

private:
  uint32_t m_width;
  uint32_t m_height;
  uint32_t m_depth;
  uint32_t m_vao;
  uint32_t m_vbo;
  /* std::array<float, 12> m_edges; */
  std::array<float, 72> m_vertices;

  auto SetupBox() -> void;
};
