#pragma once

#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include <concepts>
#include "VertexBuffer.h"
#include <iostream>

namespace sim3D {

class ElementBuffer {
public:
  uint32_t m_ID;

  ElementBuffer() {
    glad_glGenBuffers(1, &m_ID);
  };

  template<typename T>
  requires container<T>
  auto SetData(const T& data) -> void {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size()*sizeof(uint32_t), data.data(), GL_STATIC_DRAW);
  }
  
  auto Bind() -> void {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
  }

  auto Unbind() -> void {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  auto Delete() -> void {
    glad_glDeleteBuffers(1, &m_ID);
  }


private:
  
};

}
