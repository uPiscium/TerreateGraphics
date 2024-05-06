#version 330 core
in vec3 vNormal;
in vec2 vUV;

out vec4 fragColor;

// uniform sampler2D uTexture;

void main() {
  // fragColor = texture(uTexture, vUV);
  fragColor = vec4(1.0f);
}
