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
