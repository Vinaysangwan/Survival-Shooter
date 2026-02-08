#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
  StaticShader();
  ~StaticShader();

  void LoadTransformationMatrix(const glm::mat4 &mat);
  void LoadProjectionMatrix(const glm::mat4 &mat);
  
private:
  void GetAllUniformLocations() override;

private:
  GLint m_TransformationMatrixLocation;
  GLint m_ProjectionMatrixLocation;
};
