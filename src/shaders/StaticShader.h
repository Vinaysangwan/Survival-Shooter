#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
  StaticShader();
  ~StaticShader();

  void LoadTransformationMatrix(const glm::mat4 &mat);
  void LoadProjectionMatrix(const glm::mat4 &mat);
  void LoadViewMatrix(const glm::mat4 &mat);
  void LoadLightData(const glm::vec3 &lightPos, const glm::vec3 &lightColor);
  void LoadSpecularData(float shineDamper, float reflectivity);
  
private:
  void GetAllUniformLocations() override;

private:
  GLint m_TransformationMatrixLocation;
  GLint m_ProjectionMatrixLocation;
  GLint m_ViewMatrixLocation;
  
  GLint m_LightPosLocation;
  GLint m_LightColorLocation;
  GLint m_ShineDamperLocation;
  GLint m_ReflectivityLocation;
};
