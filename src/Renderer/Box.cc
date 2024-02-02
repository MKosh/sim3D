#include "Box.h"
#include <glad/gl.h>

auto Box::SetupBox() -> void {
  m_vertices = {
    // Back Top
    -0.5,  0.5,  0.5,
     0.5,  0.5,  0.5,
    // Back left
     0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,
    // Back bottom
     0.5, -0.5,  0.5,
    -0.5, -0.5,  0.5,
    // Back right
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,
    // Front top
    -0.5,  0.5, -0.5,
     0.5,  0.5, -0.5,
    // Front left
     0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,
    // Front bottom
     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    // Front right
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,
    // Left top
     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,
    // Left bottom
     0.5, -0.5,  0.5,
     0.5, -0.5, -0.5,
    // Right top
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    // Right bottom
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5
  };

  glad_glGenVertexArrays(1, &m_vao);
  glad_glGenBuffers(1, &m_vbo);

  glad_glBindVertexArray(m_vao);
  glad_glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glad_glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
  glad_glEnableVertexAttribArray(0);
  glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glad_glEnableVertexAttribArray(0);
  glad_glBindVertexArray(0);
  glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto Box::Draw() -> void {
  glad_glBindVertexArray(m_vao);
  glad_glDrawArrays(GL_LINES, 0, 72/3);
}
