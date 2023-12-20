#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include <concepts>
#include <iostream>

template<typename T>
concept container = requires(T t) {
  t.data();
  t.size();
};

namespace sim3D {

class VertexBuffer {
public:
  uint32_t m_ID;

  VertexBuffer() {
    glad_glGenBuffers(1, &m_ID);
  };

  template<typename T>
  requires container<T>
  auto SetData(const T& data) -> void {
    glad_glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glad_glBufferData(GL_ARRAY_BUFFER, data.size()*32, data.data(), GL_STATIC_DRAW);
  }

  template<typename T>
  requires container<T>
  auto SetData(const T& data, std::size_t size) {
    glad_glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glad_glBufferData(GL_ARRAY_BUFFER, data.size()*size, data.data(), GL_STATIC_DRAW);
  }

  auto Bind() const -> void {
    glad_glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  }

  auto Unbind() const -> void {
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  auto Delete() -> void {
    glad_glDeleteBuffers(1, &m_ID);
  }

  auto GetID() const -> uint32_t { return m_ID; }


private:
  
};

}
