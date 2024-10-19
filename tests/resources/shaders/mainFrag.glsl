#version 430 core
in vec3 vNormal;
in vec2 vUV;
in vec3 vColor;

out vec4 fragColor;

uniform sampler2DArray uTexture;

vec4 sampleTexture(sampler2DArray target, vec2 uv) {
  if (uv.x < 0.5f) {
    if (uv.y < 0.5f) {
      return texture(target, vec3(uv, 0));
    } else {
      return texture(target, vec3(uv, 1));
    }
  } else {
    if (uv.y < 0.5f) {
      return texture(target, vec3(uv, 2));
    } else {
      return texture(target, vec3(uv, 3));
    }
  }
}

vec4 sampleFrom0(sampler2DArray target, vec2 uv) {
  return texture(target, vec3(uv, 0));
}

void main() {
  // vec4 color = sampleTexture(uTexture, vUV);
  vec4 color = sampleFrom0(uTexture, vUV);
  if (color.a < 0.1f) {
    discard;
  }
  fragColor = color;
}
