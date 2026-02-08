#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Prepare()
{
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(const RawModel &rawModel)
{
  glBindVertexArray(rawModel.vaoID);
  glEnableVertexAttribArray(0);

  glDrawArrays(GL_TRIANGLES, 0, rawModel.vertexCount);

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
