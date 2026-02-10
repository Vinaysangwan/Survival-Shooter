#include "Loader.h"
#include "core/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Loader::Loader()
{
}

Loader::~Loader()
{
  // Delete All VAOs
  for (GLuint vao : vaos)
  {
    glDeleteVertexArrays(1, &vao);
  }
  vaos.clear();

  // Delete All VBOs
  for (GLuint vbo : vbos)
  {
    glDeleteBuffers(1, &vbo);
  }
  vbos.clear();

  // Delete All Textures
  for (GLuint texture : textures)
  {
    glDeleteTextures(1, &texture);
  }
  textures.clear();
}

RawModel Loader::LoadToVAO(const std::vector<float> &vertices,
                           const std::vector<float> &texCoords,
                           const std::vector<unsigned int> &indices)
{
  GLuint vaoID = GenerateVAOID();
  glBindVertexArray(vaoID);
  StoreElementArrayData(indices);

  StoreDataInAttribList(0, 3, vertices);
  StoreDataInAttribList(1, 2, texCoords);

  glBindVertexArray(0);
  
  return RawModel(vaoID, indices.size());
}

GLuint Loader::loadTextureID(const char *filePath)
{
  GLuint textureID;
  glGenTextures(1, &textureID);
  textures.push_back(textureID);

  glBindTexture(GL_TEXTURE_2D, textureID);

  int width, height, nChannels;
  unsigned char *data = stbi_load(filePath, &width, &height, &nChannels, 4);
  if(!data)
  {
    LOG_ASSERT(false, "Failed to Open the Texture File: {}", filePath);
  }

  // Texture Parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);

  return textureID;
}

GLuint Loader::GenerateVAOID()
{
  GLuint vaoID;
  glGenVertexArrays(1, &vaoID);
  vaos.push_back(vaoID);

  return vaoID;
}

void Loader::StoreDataInAttribList(int attribNumber, int coordinateSize, const std::vector<float> &data)
{
  GLuint vboID;
  glGenBuffers(1, &vboID);
  vbos.push_back(vboID);
  
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(attribNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreElementArrayData(const std::vector<unsigned int> &data)
{
  GLuint vboID;
  glGenBuffers(1, &vboID);
  vbos.push_back(vboID);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW); 
}
