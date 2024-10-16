#version 430 core
in vec3 vNormal;
in vec2 vUV;
in vec3 vColor;

out vec4 fragColor;

uniform sampler2DArray uTexture;

void main() {
  // if (vUV.x < 0.5f) {
  //   if (vUV.y < 0.5f) {
  //     fragColor = texture(uTexture, vec3(vUV, 0));
  //   } else {
  //     fragColor = texture(uTexture, vec3(vUV, 1));
  //   }
  // } else {
  //   if (vUV.y < 0.5f) {
  //     fragColor = texture(uTexture, vec3(vUV, 2));
  //   } else {
  //     fragColor = texture(uTexture, vec3(vUV, 3));
  //   }
  // }
  fragColor = texture(uTexture, vec3(vUV, 0));
}
