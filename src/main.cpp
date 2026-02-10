#include "pch.h"
#include "core/Display.h"
#include "core/Logger.h"
#include "models/Loader.h"
#include "renderer/Renderer.h"
#include "toolbox/Utils.h"
#include "entities/Camera.h"
#include "inputs/Input.h"

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

  // Vertices
  std::vector<float> vertices = {
    -0.5f,0.5f,-0.5f,	
    -0.5f,-0.5f,-0.5f,	
    0.5f,-0.5f,-0.5f,	
    0.5f,0.5f,-0.5f,		
    
    -0.5f,0.5f,0.5f,	
    -0.5f,-0.5f,0.5f,	
    0.5f,-0.5f,0.5f,	
    0.5f,0.5f,0.5f,
    
    0.5f,0.5f,-0.5f,	
    0.5f,-0.5f,-0.5f,	
    0.5f,-0.5f,0.5f,	
    0.5f,0.5f,0.5f,
    
    -0.5f,0.5f,-0.5f,	
    -0.5f,-0.5f,-0.5f,	
    -0.5f,-0.5f,0.5f,	
    -0.5f,0.5f,0.5f,
    
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,-0.5f,
    0.5f,0.5f,-0.5f,
    0.5f,0.5f,0.5f,
    
    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,0.5f
  };

  // Texture Coords
  std::vector<float> textureCoords = {
    0,0,
    0,1,
    1,1,
    1,0,			
    0,0,
    0,1,
    1,1,
    1,0,			
    0,0,
    0,1,
    1,1,
    1,0,
    0,0,
    0,1,
    1,1,
    1,0,
    0,0,
    0,1,
    1,1,
    1,0,
    0,0,
    0,1,
    1,1,
    1,0
  };

  // Indices
  std::vector<unsigned int> indices = {
    0,1,3,	
    3,1,2,	
    4,5,7,
    7,5,6,
    8,9,11,
    11,9,10,
    12,13,15,
    15,13,14,	
    16,17,19,
    19,17,18,
    20,21,23,
    23,21,22
  };
  
  // Init Models
  RawModel rawModel = loader.LoadToVAO(vertices, textureCoords, indices);
  ModelTexture texture = ModelTexture{loader.loadTextureID("assets/textures/Ship.png")};
  TexturedModel model = TexturedModel{
    .rawModel = rawModel,
    .texture = texture
  };

  // Init Entity
  Entity entity(model, glm::vec3(0, 0, -2), glm::vec3(0), 1);  

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

    entity.rotate(1, 1, 0);
    camera.move();

    renderer.Prepare();
    shader.Start();
    shader.LoadViewMatrix(ViewMatrix(camera.GetPosition(), camera.GetPitch(), camera.GetYaw(), camera.GetRoll()));
    renderer.Render(entity, shader);
    shader.Stop();

    display.SwapBuffers();
  }
}
