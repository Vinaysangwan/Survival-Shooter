#version 430 core

// Inputs
layout (location = 0) in vec2 inTexCoords;

// Outputs
layout (location = 0) out vec4 outColor;
layout (location = 1) in vec3 inSurfaceNormal;
layout (location = 2) in vec3 inToLightVec;

// Uniforms
uniform sampler2D uTextureSampler;
uniform vec3 uLightColor;

void main()
{
  vec4 textureColor = texture(uTextureSampler, inTexCoords);

  vec3 unitToLightVec = normalize(inToLightVec);
  float brightness = max(dot(inSurfaceNormal, unitToLightVec), 0.0);
  vec3 diffuseLight = uLightColor * brightness;

  outColor = textureColor * vec4(diffuseLight, 1.0);
}
