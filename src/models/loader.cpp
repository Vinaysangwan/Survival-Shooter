#include "loader.h"

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
}

RawModel Loader::LoadToVAO(const std::vector<float> &vertices)
{
  GLuint vaoID = GenerateVAOID();
  glBindVertexArray(vaoID);

  StoreDataInAttribList(0, 3, vertices);

  glBindVertexArray(0);
  
  return RawModel(vaoID, vertices.size() / 3);
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
