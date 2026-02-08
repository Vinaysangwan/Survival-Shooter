#include "StaticShader.h"

constexpr const char* VERTEX_FILE_PATH = "assets/shaders/Vertex.vert";
constexpr const char* FRAGMENT_FILE_PATH = "assets/shaders/Fragment.frag";

StaticShader::StaticShader()
  : ShaderProgram(VERTEX_FILE_PATH, FRAGMENT_FILE_PATH)
{
}

StaticShader::~StaticShader()
{
}
