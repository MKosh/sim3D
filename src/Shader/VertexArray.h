#pragma once

#include <cstdint>
#include <memory>
#include <sys/types.h>
#include <vector>
#include <glad/gl.h>
#include <concepts>
#include "Shader/VertexBuffer.h"
#include <iostream>

namespace sim3D {

struct VertexBufferElement {
  uint32_t type;
  uint32_t count;
  uint32_t normalized;

  static auto GetSizeOfType(uint32_t type) -> uint32_t {
    switch (type) {
      case GL_FLOAT: return 4;
      case GL_UNSIGNED_INT: return 4;
      case GL_UNSIGNED_BYTE: return 1;
    }
    assert(false);
    return 0;
  }
};

class VertexBufferLayout {
public:

  VertexBufferLayout() : m_stride{0} {};
  template <typename T>
  auto Push([[maybe_unused]]uint32_t count) -> void {
    // static_assert(false);
  }
  template <>
  auto Push<float>(uint32_t count) -> void {
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
  }
  template <>
  auto Push<uint32_t>(uint32_t count) -> void {
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * sizeof(uint32_t);
  }

  inline auto GetStride() const -> uint32_t { return m_stride; }
  inline auto GetElements() const -> const std::vector<VertexBufferElement>& { return m_elements; }
private:
  std::vector<VertexBufferElement> m_elements;
  uint32_t m_stride;
};

class VertexArray {
public:
  uint32_t m_ID;

  VertexArray() {
    glad_glGenVertexArrays(1, &m_ID);
  };

  auto Bind() const -> void {
    glad_glBindVertexArray(m_ID);
  }

  auto Unbind() const -> void {
    glad_glBindVertexArray(0);
  }

  auto Delete() -> void {
    glad_glDeleteVertexArrays(1, &m_ID);
  }

  auto SetDivisor(uint32_t index, uint32_t divisor) const -> void {
    Bind();
    glad_glVertexAttribDivisor(index, divisor);
  }

  auto LinkVBO(const VertexBuffer& VBO, const VertexBufferLayout& layout) const -> void {
    VBO.Bind();
    const auto& elements = layout.GetElements();
    uint64_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); ++i) {
      const auto& element = elements[i];
      glad_glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (const void*)offset);
      glad_glEnableVertexAttribArray(i);
      offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    VBO.Unbind();
  }

private:
  
};

}
      // std::cout << "index: " << i << '\n'
      //           << "count: " << element.count << '\n'
      //           << "type:  " << VertexBufferElement::GetSizeOfType(element.type)<< '\n'
      //           << "norm:  " << element.normalized << '\n'
      //           << "stride:" << layout.GetStride() << '\n'
      //           << "offset:" << offset << '\n';
      // std::cout << "-------\n";
