#include "pch.h"
#include "Renderer.h"
#include "toolbox/Utils.h"

Renderer::Renderer(StaticShader &shader)
  : m_Shader(shader)
{
  CreateProjectionMatrix();

  shader.Start();
  shader.LoadProjectionMatrix(m_ProjectionMatrix);
  shader.Stop();
}

Renderer::~Renderer()
{
}

void Renderer::Render(const std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher> &entities)
{
  for (auto it = entities.begin(); it != entities.end(); it++)
  {
    const TexturedModel &model = it->first;    
    LoadTexture(model);

    for (const Entity& entity : it->second)
    {
      SetEntityData(entity);      
      glDrawElements(GL_TRIANGLES, model.rawModel.vertexCount, GL_UNSIGNED_INT, nullptr);
    }

    UnLoadTexture();
  }
}

void Renderer::LoadTexture(const TexturedModel &model)
{
  const RawModel &rawModel = model.rawModel;
  const ModelTexture &texture = model.texture;

  glBindVertexArray(rawModel.vaoID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.textureID);

  m_Shader.LoadSpecularData(texture.shineDamper, texture.reflectivity);
}

void Renderer::UnLoadTexture()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void Renderer::SetEntityData(const Entity& entity)
{
   glm::mat4 transMat = TransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
  m_Shader.LoadTransformationMatrix(transMat);
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

