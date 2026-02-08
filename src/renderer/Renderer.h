#pragma once

#include "models/Models.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void Prepare();
  void Render(const RawModel &rawModel);
};
