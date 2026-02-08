#pragma once

#include "textures/ModelTexture.h"

struct RawModel
{
  unsigned int vaoID;
  int vertexCount;
};

struct TexturedModel
{
  RawModel rawModel;
  ModelTexture texture;
};
