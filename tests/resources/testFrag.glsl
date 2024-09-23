#version 330 core
in vec3 vNormal;
in vec2 vUV;
in vec3 vColor;

out vec4 fragColor;

uniform sampler2D uTexture;

void main() {
  vec4 tex = texture(uTexture, vUV);
  fragColor = vec4(tex.rgb, 1.0) * vec4(vColor, 1.0) * 1.5;
}
