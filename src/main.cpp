#include "pch.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "models/loader.h"
#include "renderer/Renderer.h"
#include "toolbox/Utils.h"
#include "shaders/StaticShader.h"

int main()
{
  // Init Display
  Display display("Survival Shooter", 1280, 720);
  display.SetVsync(true);

  // Init Loader
  Loader loader;

  // Init Renderer
  Renderer renderer;

  // Init Shaders
  StaticShader shader;

  // Vertices
  std::vector<float> vertices = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };
  
  // RawModel
  RawModel rawModel = loader.LoadToVAO(vertices);

  // Main Game Loop
  while(display.IsRunning())
  {
    display.Update();

    renderer.Prepare();
    shader.Start();
    renderer.Render(rawModel);
    shader.Stop();

    display.SwapBuffers();
  }
}
