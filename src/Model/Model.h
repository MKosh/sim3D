#pragma once

#include "Shader/ElementBuffer.h"
#include "Shader/Shader.h"
#include "Mesh.h"
#include "Shader/VertexBuffer.h"

#include <cstdint>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
  Model(const std::string& path);
  auto Draw(Shader& shader) -> void;
  auto AddProperty(const sim3D::VertexBuffer& vbo, const sim3D::VertexBufferLayout& layout, const uint32_t index = 0) const -> void;
  auto SetPropertyDivisor(uint32_t index, uint32_t divisor) const -> void;
  auto SetInstances(uint32_t intstances) -> void;
  auto BindVAO() -> void;

private:
  std::vector<Mesh> m_meshes;
  std::string m_directory;
  std::vector<Texture> m_textures_loaded;
  // std::filesystem::path m_directory;

  auto LoadModel(const std::string& path) -> void;
  auto ProcessNode(aiNode* node, const aiScene* scene) -> void;
  auto ProcessMesh(aiMesh* mesh, const aiScene* scene) -> Mesh; 
  auto LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name) -> std::vector<Texture>;
};
