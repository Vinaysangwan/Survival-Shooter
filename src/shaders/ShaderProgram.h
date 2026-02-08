#pragma once

#include <glad/glad.h>

class ShaderProgram
{
public:
  ShaderProgram(const char *vertexShaderFilePath, const char *fragmentShaderFilePath);
  ~ShaderProgram();

  void Start();
  void Stop();

private:
  GLuint CreateShader(const char *shaderFilePath, GLenum type);

private:
  GLuint m_VertexID;
  GLuint m_FragmentID;
  GLuint m_ProgramID;
};
