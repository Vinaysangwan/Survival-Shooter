#include "pch.h"
#include "MasterRenderer.h"
#include "toolbox/Utils.h"

MasterRenderer::MasterRenderer()
{
  m_Renderer = new Renderer(m_Shader);
}

MasterRenderer::~MasterRenderer()
{
  delete m_Renderer;
}

void MasterRenderer::Prepare()
{
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::Render(const Light &sun, const Camera &camera)
{
  Prepare();

  m_Shader.Start();
  m_Shader.LoadLightData(sun.GetPosition(), sun.GetColor());
  m_Shader.LoadViewMatrix(ViewMatrix(camera.GetPosition(), camera.GetPitch(), camera.GetYaw(), camera.GetRoll()));
  m_Renderer->Render(m_Entities);
  m_Shader.Stop();

  m_Entities.clear();
}

void MasterRenderer::AddEntity(const Entity &entity)
{
  m_Entities[entity.GetModel()].push_back(entity);
}

