#include "Mesh.h"
#include <cstdint>
#include <iostream>
#include <vector>


Mesh::Mesh(std::vector<Vertex>vertices, std::vector<uint32_t> indicies, std::vector<Texture> textures) :
           m_vertices{vertices}, m_indicies{indicies}, m_textures{textures}{
  SetupMesh();
}

auto Mesh::SetupMesh() -> void {

  m_vao.Bind();
  m_vbo.SetData(m_vertices);
  m_ebo.SetData(m_indicies);
  sim3D::VertexBufferLayout layout;
  layout.Push<float>(3); // Position
  layout.Push<float>(3); // Normal
  layout.Push<float>(2); // Texture

  m_vao.LinkVBO(m_vbo, layout);
  m_vao.Unbind();
}

auto Mesh::Draw(Shader& shader) -> void {
  uint32_t diffuseNr = 1;
  uint32_t specularNr = 1;
  uint32_t normalNr = 1;
  uint32_t heightNr = 1;
    /* aiColor3D color(0.0f, 0.0f, 0.0f); */
    /* material->Get(AI_MATKEY_COLOR_DIFFUSE, color); */
  for (uint32_t i = 0; i < m_textures.size(); ++i) {
    glad_glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = m_textures[i].type;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);
    else if (name == "texture_normal")
      number = std::to_string(normalNr++);
    else if (name == "texture_height")
      number = std::to_string(heightNr++);

    shader.SetInt((name + number).c_str(), i);
    glad_glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
  }

  // Draw mesh
  if (m_instances == 1) {
    m_vao.Bind();
    glad_glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
    m_vao.Unbind();
  } else if (m_instances > 1) {
    m_vao.Bind();
    glad_glDrawElementsInstanced(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0, m_instances);
    m_vao.Unbind();
  } else {
    std::cout << "ERROR: incorrect number of instances, cannot draw mesh: " << m_instances << " instances requested\n";
  }
  
  glad_glActiveTexture(GL_TEXTURE0);
}

auto Mesh::SetDivisor(uint32_t index, uint32_t divisor) const -> void {
  m_vao.SetDivisor(index, divisor);
}


auto Mesh::AddVBO(const sim3D::VertexBuffer& vbo, const sim3D::VertexBufferLayout& layout, const uint32_t index) const -> void {
  m_vao.Bind();
  m_vao.LinkVBO(vbo, layout, index);
  std::cout << m_instances << " instances requested\n";
  m_vao.Unbind();
}

auto Mesh::BindVAO() -> void {
  m_vao.Bind();
}
