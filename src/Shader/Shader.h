#pragma once

#include <cstdint>
#include <glm/fwd.hpp>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:

  Shader(const std::string& vertex_path, const std::string& fragment_path);

  auto Use() -> void;
  auto Delete() -> void;

  auto SetBool(const std::string& name, bool value) -> void;
  auto SetInt(const std::string& name, int value) -> void;
  auto SetFloat(const std::string& name, float value) -> void;
  auto SetMat4(const std::string& name, const glm::mat4& value) -> void;
  auto SetUniform4f(const std::string& name, const glm::vec4 vec) -> void;
  auto SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3) -> void;
  auto SetVec3f(const std::string& name, const glm::vec3 vec) -> void;
  auto SetVec3f(const std::string& name, const float v0, const float v1, const float v2) -> void;


private:
  uint32_t m_ID;
  std::unordered_map<std::string, int32_t> m_UniformLocationCache;

  auto GetUniformLocation(const std::string& name) -> int32_t;
};
