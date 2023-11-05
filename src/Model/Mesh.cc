#include "Mesh.h"
#include <cstdint>


Mesh::Mesh(std::vector<Vertex>vertices, std::vector<uint32_t> indicies, std::vector<Texture> textures) :
           m_vertices{vertices}, m_indicies{indicies}, m_textures{textures} {
  SetupMesh();
}

auto Mesh::SetupMesh() -> void {
  glad_glGenVertexArrays(1, &m_vao);
  glad_glGenBuffers(1, &m_vbo);
  glad_glGenBuffers(1, &m_ebo);

  glad_glBindVertexArray(m_vao);
  
  glad_glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glad_glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
  
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(uint32_t), &m_indicies[0], GL_STATIC_DRAW);

  // Vertex positions
  glad_glEnableVertexAttribArray(0);
  glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  // Vertex normals
  glad_glEnableVertexAttribArray(1);
  glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  // Vertex texture coords
  glad_glEnableVertexAttribArray(2);
  glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

  glad_glBindVertexArray(0);
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
  glad_glBindVertexArray(m_vao);
  glad_glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(m_indicies.size()), GL_UNSIGNED_INT, 0);
  glad_glBindVertexArray(0);
  
  glad_glActiveTexture(GL_TEXTURE0);
}
