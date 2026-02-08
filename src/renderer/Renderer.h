#pragma once

#include "entities/Entity.h"
#include "shaders/StaticShader.h"

class Renderer
{
public:
  Renderer(StaticShader &shader);
  ~Renderer();

  void Prepare();
  void Render(const Entity &entity, StaticShader &shader);

private:
  void CreateProjectionMatrix();
  
private:
  glm::mat4 m_ProjectionMatrix;  
};
