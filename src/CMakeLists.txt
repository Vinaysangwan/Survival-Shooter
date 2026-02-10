target_sources(${PROJECT_NAME} PRIVATE
  main.cpp

  core/Display.cpp
  core/Logger.cpp

  entities/Entity.cpp
  entities/Camera.cpp

  inputs/Input.cpp
  
  models/Loader.cpp

  renderer/Renderer.cpp

  shaders/ShaderProgram.cpp
  shaders/StaticShader.cpp

  toolbox/Utils.cpp
)