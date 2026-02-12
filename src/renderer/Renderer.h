#pragma once

#include <unordered_map>
#include <vector>

#include "entities/Entity.h"
#include "models/Models.h"
#include "shaders/StaticShader.h"

class Renderer
{
public:
  Renderer(StaticShader &shader);
  ~Renderer();

  void Render(const std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher> &entities);

private:
  void LoadTexture(const TexturedModel &model);
  void UnLoadTexture();
  void SetEntityData(const Entity& entity);

  void CreateProjectionMatrix();
  
private:
  glm::mat4 m_ProjectionMatrix;  
  StaticShader m_Shader;
};
