#include "pch.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "models/Loader.h"
#include "renderer/Renderer.h"
#include "toolbox/Utils.h"
#include "entities/Camera.h"
#include "inputs/Input.h"
#include "entities/Light.h"

int main()
{
  // Init Display
  Display display("Survival Shooter", 1280, 720);
  display.SetVsync(true);

  // Init Loader
  Loader loader;

  // Init Shaders
  StaticShader shader;

  // Init Renderer
  Renderer renderer(shader);

  // Init Models
  RawModel rawModel = loader.LoadModel("assets/textures/stall.obj");
  ModelTexture texture = ModelTexture{loader.loadTextureID("assets/textures/stallTexture.png")};
  TexturedModel model = TexturedModel{
    .rawModel = rawModel,
    .texture = texture
  };

  // Init Entity
  Entity entity(model, glm::vec3(0, 0, -20), glm::vec3(0), 1);  

  // Init Light
  Light light(glm::vec3(0, 20, -5), glm::vec3(1, 1, 1));

  // Init Camera
  Camera camera(glm::vec3(0, 0, 0), 0, 0, 0);

  // Main Game Loop
  while(display.IsRunning())
  {
    display.Update();
    if (KeyDown(GLFW_KEY_ESCAPE))
    {
      display.close();
    }

    camera.move();
    entity.move();

    renderer.Prepare();
    shader.Start();
    shader.LoadLightData(light.GetPosition(), light.GetColor());
    shader.LoadViewMatrix(ViewMatrix(camera.GetPosition(), camera.GetPitch(), camera.GetYaw(), camera.GetRoll()));
    renderer.Render(entity, shader);
    shader.Stop();

    display.SwapBuffers();
  }
}
