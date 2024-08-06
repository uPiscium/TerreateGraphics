#version 330 core
in vec2 vUV;

out vec4 fragColor;

uniform sampler2D uTexture;
uniform vec3 uColor;

void main() {
  float alpha = texture(uTexture, vUV).r;
  // fragColor = vec4(uColor, alpha);
  if (alpha < 0.1) {
    discard;
  }
  fragColor = vec4(uColor, alpha);
}
