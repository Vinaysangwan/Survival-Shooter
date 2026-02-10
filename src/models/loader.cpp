#include "Loader.h"
#include "core/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #############################################################################
//                           Constants
// #############################################################################
constexpr unsigned int ASSIMP_LOAD_FLAGS = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices;

// #############################################################################
//                           Constants
// #############################################################################
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
                           const std::vector<float> &normals,
                           const std::vector<unsigned int> &indices)
{
  GLuint vaoID = GenerateVAOID();
  glBindVertexArray(vaoID);
  StoreElementArrayData(indices);

  StoreDataInAttribList(0, 3, vertices);
  StoreDataInAttribList(1, 2, texCoords);
  StoreDataInAttribList(2, 3, normals);

  glBindVertexArray(0);
  
  return RawModel(vaoID, indices.size());
}

RawModel Loader::LoadModel(const std::string & path)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(path, ASSIMP_LOAD_FLAGS);

  if (!scene || !scene->HasMeshes())
  {
    LOG_ASSERT(false, "Failed to Open the Model: {}", path);
  }

  aiMesh *mesh = scene->mMeshes[0];

  std::vector<float> position;
  std::vector<float> textureCoords;
  std::vector<float> normals;
  std::vector<unsigned int> indices;

  // Vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    position.push_back(mesh->mVertices[i].x);
    position.push_back(mesh->mVertices[i].y);
    position.push_back(mesh->mVertices[i].z);
  
    // Textured Coords
    if (mesh->mTextureCoords[0])
    {
      textureCoords.push_back(mesh->mTextureCoords[0][i].x);
      textureCoords.push_back(mesh->mTextureCoords[0][i].y);
    }
    else
    {
      textureCoords.push_back(0.0f);
      textureCoords.push_back(0.0f);
    }

    // Normals
    if (mesh->mNormals)
    {
      normals.push_back(mesh->mNormals[i].x);
      normals.push_back(mesh->mNormals[i].y);
      normals.push_back(mesh->mNormals[i].z);
    }
    else
    {
      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);
    }
  }

  // Indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  return LoadToVAO(position, textureCoords, normals, indices);
}

GLuint Loader::loadTextureID(const char* filePath, int texWrap , int texFilter)
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, texWrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilter);

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
