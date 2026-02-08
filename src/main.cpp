#include "pch.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "models/loader.h"
#include "renderer/Renderer.h"
#include "toolbox/Utils.h"

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
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };

  // Texture Coords
  std::vector<float> textureCoords = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
  };

  // Indices
  std::vector<unsigned int> indices = {
    0, 1, 3,
    3, 1, 2
  };
  
  // Init Models
  RawModel rawModel = loader.LoadToVAO(vertices, textureCoords, indices);
  ModelTexture texture = ModelTexture{loader.loadTextureID("assets/textures/Ship.png")};
  TexturedModel model = TexturedModel{
    .rawModel = rawModel,
    .texture = texture
  };

  // Init Entity
  Entity entity(model, glm::vec3(0, 0, 0), glm::vec3(0), 1);  

  // Main Game Loop
  while(display.IsRunning())
  {
    display.Update();

    entity.rotate(0, 1, 0);

    renderer.Prepare();
    shader.Start();
    renderer.Render(entity, shader);
    shader.Stop();

    display.SwapBuffers();
  }
}
