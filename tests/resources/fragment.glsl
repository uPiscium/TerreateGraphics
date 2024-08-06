#version 330 core
in vec3 vNormal;
in vec2 vUV;
in vec3 vColor;

out vec4 fragColor;

uniform sampler2D uTexture;

float solalization(float c) {
  return sin(7 * c);
}

float convert(float c) {
  return c;
}

vec4 effect(vec3 color) {
  float dist = length(vUV - vec2(0.5));
  return vec4(color, 1.0) * (1.0 - dist);
}

void main() {
  // fragColor = effect(vColor);
  vec4 tex = texture(uTexture, vUV);
  fragColor = vec4(tex.rgb, 1.0) * vec4(vColor, 1.0) * 1.5;
}
