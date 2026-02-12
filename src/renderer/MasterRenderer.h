#pragma once

#include <unordered_map>
#include <vector>

#include "models/Models.h"
#include "Renderer.h"
#include "entities/Light.h"
#include "entities/Camera.h"

class MasterRenderer
{
public:
   MasterRenderer();
  ~MasterRenderer();

  void Render(const Light &sun, const Camera &camera);
  void AddEntity(const Entity &entity);

private:
  void Prepare();

private:
  StaticShader m_Shader;
  Renderer *m_Renderer;

  std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher> m_Entities;
};

