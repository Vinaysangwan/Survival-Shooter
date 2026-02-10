#version 430 core

// Inputs
layout (location = 0) in vec2 inTexCoords;

// Outputs
layout (location = 0) out vec4 outColor;
layout (location = 1) in vec3 inSurfaceNormal;
layout (location = 2) in vec3 inToLightVec;
layout (location = 3) in vec3 inToCameraVec;

// Uniforms
uniform sampler2D uTextureSampler;
uniform vec3 uLightColor;
uniform float uShineDamper;
uniform float uReflectivity;

void main()
{
  vec4 textureColor = texture(uTextureSampler, inTexCoords);

  vec3 unitToLightVec = normalize(inToLightVec);
  vec3 unitToCameraVec = normalize(inToCameraVec);
  vec3 unitNormal = normalize(inSurfaceNormal);
  
  float brightness = max(dot(unitNormal, unitToLightVec), 0.15);
  vec3 diffuseLight = uLightColor * brightness;

  vec3 reflectedLight = reflect(-unitToLightVec, unitNormal);
  float specularFactor = max(dot(unitToCameraVec, reflectedLight), 0.0);
  float dampedFactor = pow(specularFactor, uShineDamper) * uReflectivity;
  vec3 specularLight = dampedFactor * uLightColor;

  outColor = textureColor * vec4(diffuseLight, 1.0) + vec4(specularLight, 1.0);
}
