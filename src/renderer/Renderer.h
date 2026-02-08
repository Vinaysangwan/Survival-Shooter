#pragma once

#include "entities/Entity.h"
#include "shaders/StaticShader.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void Prepare();
  void Render(const Entity &entity, StaticShader &shader);
};
