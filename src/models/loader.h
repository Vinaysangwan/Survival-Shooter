#pragma once

#include "Models.h"

#include <vector>

class Loader
{
public:
  Loader();
  ~Loader();

  RawModel LoadToVAO(const std::vector<float> &vertices);

private:
  GLuint GenerateVAOID();

  void StoreDataInAttribList(int attribNumber, int coordinateSize, const std::vector<float> &data);

private:
  std::vector<GLuint> vaos;
  std::vector<GLuint> vbos;
};
