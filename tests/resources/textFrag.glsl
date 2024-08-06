#version 330 core
in vec2 vUV;

out vec4 fragColor;

uniform sampler2D uTexture;

void main() {
  float alpha = texture(uTexture, vUV).r;
  // if (alpha < 0.6) discard;
  // else fragColor = vec4(1.0);
  fragColor = vec4(1.0, 1.0, 1.0, alpha);
}
