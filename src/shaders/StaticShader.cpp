#include "StaticShader.h"

constexpr const char* VERTEX_FILE_PATH = "assets/shaders/Vertex.vert";
constexpr const char* FRAGMENT_FILE_PATH = "assets/shaders/Fragment.frag";

StaticShader::StaticShader()
  : ShaderProgram(VERTEX_FILE_PATH, FRAGMENT_FILE_PATH)
{
  GetAllUniformLocations();
}

StaticShader::~StaticShader()
{
}

void StaticShader::GetAllUniformLocations()
{
  m_TransformationMatrixLocation = GetUniformLocation("uTransformationMatrix");
}

void StaticShader::LoadTransformationMatrix(const glm::mat4 &mat)
{
  UniformLoadMat4(m_TransformationMatrixLocation, mat);
}
