#include "pch.h"
#include "ShaderProgram.h"
#include "toolbox/Utils.h"
#include "core/Logger.h"

ShaderProgram::ShaderProgram(const char *vertexShaderFilePath, const char *fragmentShaderFilePath)
{
  m_VertexID = CreateShader(vertexShaderFilePath, GL_VERTEX_SHADER);
  m_FragmentID = CreateShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);

  m_ProgramID = glCreateProgram();
  glAttachShader(m_ProgramID, m_VertexID);
  glAttachShader(m_ProgramID, m_FragmentID);
  glLinkProgram(m_ProgramID);
  glValidateProgram(m_ProgramID);
}

ShaderProgram::~ShaderProgram()
{
  Stop();

  glDetachShader(m_ProgramID, m_VertexID);
  glDetachShader(m_ProgramID, m_FragmentID);

  glDeleteShader(m_VertexID);
  glDeleteShader(m_FragmentID);
  glDeleteProgram(m_ProgramID);
}

void ShaderProgram::Start()
{
  glUseProgram(m_ProgramID);
}

void ShaderProgram::Stop()
{
  glUseProgram(0);
}

GLint ShaderProgram::GetUniformLocation(const char * name) const
{
  GLint location = glGetUniformLocation(m_ProgramID, name);
  if (location < 0)
  {
    LOG_ASSERT(false, "Failed to Get Uniform Location: {}", name);
  }
  
  return location;
}

void ShaderProgram::UniformLoadFloat(GLint location, float val)
{
  glUniform1f(location, val);
}

void ShaderProgram::UniformLoadInt(GLint location, int val)
{
  glUniform1i(location, val);
}

void ShaderProgram::UniformLoadBool(GLint location, bool val)
{
  glUniform1i(location, val ? 1 : 0);
}

void ShaderProgram::UniformLoadVec3(GLint location, const glm::vec3 &vec)
{
  glUniform1fv(location, 1, glm::value_ptr(vec));
}

void ShaderProgram::UniformLoadMat4(GLint location, const glm::mat4 &mat)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

GLuint ShaderProgram::CreateShader(const char *shaderFilePath, GLenum type)
{
  GLuint shaderID = glCreateShader(type);

  std::string shaderSourceCode;
  ReadFile(shaderFilePath, shaderSourceCode);

  std::string shaderType = type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader";

  const char *source = shaderSourceCode.c_str();
  glShaderSource(shaderID, 1, &source, nullptr);
  glCompileShader(shaderID);

  int success;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if(success == 0)
  {
    char infoLog[1024] = {};
    glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
    LOG_ASSERT(false, "Failed to Compile {}: {}", shaderType, infoLog);
  
    return 0;
  }

  return shaderID;
}
