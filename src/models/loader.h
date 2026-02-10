#pragma once

#include "Models.h"

#include <vector>

class Loader
{
public:
  Loader();
  ~Loader();

  RawModel LoadToVAO(const std::vector<float> &vertices,
                     const std::vector<float> &texCoords,
                     const std::vector<float> &normals,
                     const std::vector<unsigned int> &indices);
  
  RawModel LoadModel(const std::string &path);

  GLuint loadTextureID(const char* filePath, int texWrap = GL_CLAMP_TO_BORDER, int texFilter = GL_LINEAR);

private:
  GLuint GenerateVAOID();

  void StoreDataInAttribList(int attribNumber, int coordinateSize, const std::vector<float> &data);
  void StoreElementArrayData(const std::vector<unsigned int> &data);

private:
  std::vector<GLuint> vaos;
  std::vector<GLuint> vbos;
  std::vector<GLuint> textures;
};
