target_sources(${PROJECT_NAME} PRIVATE
  main.cpp

  core/Display.cpp
  core/Logger.cpp

  entities/Entity.cpp
  
  models/loader.cpp

  renderer/Renderer.cpp

  shaders/ShaderProgram.cpp
  shaders/StaticShader.cpp

  toolbox/Utils.cpp
)