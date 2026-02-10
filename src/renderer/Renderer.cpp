#include "pch.h"
#include "Renderer.h"
#include "toolbox/Utils.h"

Renderer::Renderer(StaticShader &shader)
{
  CreateProjectionMatrix();

  shader.Start();
  shader.LoadProjectionMatrix(m_ProjectionMatrix);
  shader.Stop();
}

Renderer::~Renderer()
{
}

void Renderer::Prepare()
{
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(const Entity &entity, StaticShader &shader)
{
  const TexturedModel &model = entity.GetModel();
  const RawModel &rawModel = model.rawModel;
  const ModelTexture &texture = model.texture;
  
  glBindVertexArray(rawModel.vaoID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.textureID);

  shader.LoadSpecularData(texture.shineDamper, texture.reflectivity);
  
  glm::mat4 transMat = TransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
  shader.LoadTransformationMatrix(transMat);
  
  glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void Renderer::CreateProjectionMatrix()
{
  m_ProjectionMatrix = glm::perspective(
    glm::radians(70.0f),
    1280.0f / 720.0f,
    0.1f,
    1000.0f
  );
}
