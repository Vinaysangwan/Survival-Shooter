#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
  ShaderProgram(const char *vertexShaderFilePath, const char *fragmentShaderFilePath);
  ~ShaderProgram();

  void Start();
  void Stop();

protected:
  virtual void GetAllUniformLocations() = 0;
  
  GLint GetUniformLocation(const char *name) const;

  void UniformLoadFloat(GLint location, float val);
  void UniformLoadInt(GLint location, int val);
  void UniformLoadBool(GLint location, bool val);

  void UniformLoadVec3(GLint location, const glm::vec3 &vec);

  void UniformLoadMat4(GLint location, const glm::mat4 &mat);
  
private:
  GLuint CreateShader(const char *shaderFilePath, GLenum type);

private:
  GLuint m_VertexID;
  GLuint m_FragmentID;
  GLuint m_ProgramID;
};
