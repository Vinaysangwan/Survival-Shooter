#version 430 core

// Inputs
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;

// Outputs
layout (location = 0) out vec2 outTexCoords;

// Uniforms
uniform mat4 uTransformationMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
  gl_Position = uProjectionMatrix * uTransformationMatrix * vec4(inPos, 1.0);

  outTexCoords = inTexCoords;
}
