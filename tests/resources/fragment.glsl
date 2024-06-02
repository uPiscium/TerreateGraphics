#version 330 core
in vec3 vNormal;
in vec2 vUV;

out vec4 fragColor;

uniform sampler2D uTexture;

float solalization(float c) {
  return sin(7 * c);
}

float convert(float c) {
  return c;
}

vec4 effect(vec3 color) {
  float r = convert(color.r);
  float g = convert(color.g);
  float b = convert(color.b);

  if (vUV.x < 0.5 && vUV.y < 0.5) {
    return vec4(color, 1.0);
  }
  if (vUV.x >= 0.5 && vUV.y < 0.5) {
    return vec4(r, 0.5 * g, 0.5 * b, 1.0);
  }
  if (vUV.x < 0.5 && vUV.y >= 0.5) {
    return vec4(0.5 * r, g, 0.5 * b, 1.0);
  }
  return vec4(0.5 * r, 0.5 * g, b, 1.0);
}

void main() {
  vec4 color = texture(uTexture, vUV);
  fragColor = effect(color.rgb);
}
