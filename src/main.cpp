#include "pch.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "models/Loader.h"
#include "renderer/MasterRenderer.h"
#include "toolbox/Utils.h"
#include "entities/Camera.h"
#include "inputs/Input.h"
#include "entities/Light.h"

int main()
{
  // Init Display
  Display display("Survival Shooter", 1280, 720);
  bool vSync = true;
  display.SetVsync(true);

  // Init Loader
  Loader loader;

  // Init Models
  RawModel rawModel = loader.LoadModel("assets/textures/rifle.obj");
  ModelTexture texture = ModelTexture{loader.loadTextureID("assets/textures/m_rifl.bmp")};
  texture.shineDamper = 25.0f;
  texture.reflectivity = 1.0f;
  TexturedModel model = TexturedModel{
    .rawModel = rawModel,
    .texture = texture
  };

  // Init Entity
  Entity entity(model, glm::vec3(0, 0, -20), glm::vec3(0), 1);  

  // Init Light
  Light light(glm::vec3(0, 20, 0), glm::vec3(1, 1, 1));

  // Init Camera
  Camera camera(glm::vec3(0, 0, 0), 0, 0, 0);
  
  // Init Renderer
  MasterRenderer renderer;

  // Main Game Loop
  while(display.IsRunning())
  {
    display.Update();
    if (KeyDown(GLFW_KEY_ESCAPE))
    {
      display.close();
    }
    if (KeyPressed(GLFW_KEY_V))
    {
      vSync = !vSync;
      display.SetVsync(vSync);
    }

    camera.move();
    entity.move();

    renderer.AddEntity(entity);
    renderer.Render(light, camera);

    display.SwapBuffers();
  }
}

