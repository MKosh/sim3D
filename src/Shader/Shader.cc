#include <glad/gl.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
  std::string vertex_code;
  std::string fragment_code;

  std::ifstream v_shader_file;
  std::ifstream f_shader_file;

  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    v_shader_file.open(vertex_path.c_str());
    f_shader_file.open(fragment_path.c_str());

    std::stringstream v_shader_stream, f_shader_stream;

    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();
    
    v_shader_file.close();
    f_shader_file.close();

    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "Error::Shader -- File not successfully read" << std::endl;
  }
  const char* v_shader_code = vertex_code.c_str();
  const char* f_shader_code = fragment_code.c_str();

  // Compile the shaders
  uint32_t vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glad_glCreateShader(GL_VERTEX_SHADER);
  glad_glShaderSource(vertex, 1, &v_shader_code, nullptr);
  glad_glCompileShader(vertex);
  glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glad_glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    std::cout << "Error::Shader -- vertex compilation failed\n" << infoLog << std::endl;
  }


  fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
  glad_glShaderSource(fragment, 1, &f_shader_code, nullptr);
  glad_glCompileShader(fragment);
  glad_glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glad_glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    std::cout << "Error::Shader -- fragment compilation failed\n" << infoLog << std::endl;
  }

  // Create the shader program and link the shaders
  m_ID = glad_glCreateProgram();
  glad_glAttachShader(m_ID, vertex);
  glad_glAttachShader(m_ID, fragment);
  glad_glLinkProgram(m_ID);

  glad_glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glad_glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
    std::cout << "Error::Shader -- Linking program failed\n" << infoLog << std::endl;
  }

  // Delete the shaders since they're already linked an no longer needed
  glad_glDeleteShader(vertex);
  glad_glDeleteShader(fragment);

}

auto Shader::Use() -> void {
  glad_glUseProgram(m_ID);
}

auto Shader::Delete() -> void {
  glad_glDeleteProgram(m_ID);
}

auto Shader::SetBool(const std::string& name, bool value) -> void {
  glad_glUniform1i(GetUniformLocation(name), (int)value);
}

auto Shader::SetInt(const std::string& name, int32_t value) -> void {
  glad_glUniform1i(GetUniformLocation(name), value);
}

auto Shader::SetFloat(const std::string& name, float value) -> void {
  glad_glUniform1f(GetUniformLocation(name), value);
}

auto Shader::SetMat4(const std::string& name, const glm::mat4& mat) -> void {
  glad_glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

auto Shader::SetUniform4f(const std::string& name, const glm::vec4 vec) -> void {
  glad_glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

auto Shader::SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3) -> void {
  glad_glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

auto Shader::SetVec3f(const std::string& name, const glm::vec3 vec) -> void {
  glad_glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

auto Shader::SetVec3f(const std::string& name, const float v0, const float v1, const float v2) -> void {
  glad_glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

auto Shader::GetUniformLocation(const std::string& name) -> int32_t {
  if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  int32_t location = glad_glGetUniformLocation(m_ID, name.c_str());
  if (location == -1) {
    std::cout << "Warning: uniform " << name << " doesn't exist!\n";
    std::cout << "\tUniform: " << name << " with shader ID: " << m_ID << "\n\n";
  }
  
  m_UniformLocationCache[name] = location; 
  return location;
}
