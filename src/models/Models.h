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

  bool operator==(const TexturedModel& other) const
  {
    return (rawModel.vaoID == other.rawModel.vaoID && 
            texture.textureID == other.texture.textureID);
  }
};

struct TexturedModelHasher
{
  std::size_t operator()(const TexturedModel& model) const
  {
    std::size_t h1 = std::hash<int>{}(model.rawModel.vaoID);
    std::size_t h2 = std::hash<int>{}(model.texture.textureID);
    return h1 ^ (h2 << 1);
  }
};

