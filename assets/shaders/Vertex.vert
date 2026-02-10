#version 430 core

// Inputs
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 inNormal;

// Outputs
layout (location = 0) out vec2 outTexCoords;
layout (location = 1) out vec3 outSurfaceNormal;
layout (location = 2) out vec3 outToLightVec;
layout (location = 3) out vec3 outToCameraVec;

// Uniforms
uniform mat4 uTransformationMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform vec3 uLightPos;

void main()
{
  vec4 worldPos = uTransformationMatrix * vec4(inPos, 1.0);
  gl_Position = uProjectionMatrix * uViewMatrix * worldPos;

  outTexCoords = inTexCoords;
  outSurfaceNormal = (uTransformationMatrix * vec4(inNormal, 0.0)).xyz;
  outToLightVec = uLightPos - worldPos.xyz;
  outToCameraVec = vec3(inverse(uViewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPos.xyz;
}
