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
  m_ProjectionMatrixLocation = GetUniformLocation("uProjectionMatrix");
  m_ViewMatrixLocation = GetUniformLocation("uViewMatrix");
  m_LightPosLocation = GetUniformLocation("uLightPos");
  m_LightColorLocation = GetUniformLocation("uLightColor");
}

void StaticShader::LoadTransformationMatrix(const glm::mat4 &mat)
{
  UniformLoadMat4(m_TransformationMatrixLocation, mat);
}

void StaticShader::LoadProjectionMatrix(const glm::mat4 &mat)
{
  UniformLoadMat4(m_ProjectionMatrixLocation, mat);
}

void StaticShader::LoadViewMatrix(const glm::mat4 &mat)
{
  UniformLoadMat4(m_ViewMatrixLocation, mat);
}

void StaticShader::LoadLightData(const glm::vec3 &lightPos, const glm::vec3 &lightColor)
{
  UniformLoadVec3(m_LightPosLocation, lightPos);
  UniformLoadVec3(m_LightColorLocation, lightColor);
}
