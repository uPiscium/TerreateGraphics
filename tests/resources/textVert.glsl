#version 330 core
in vec3 iPosition;
in vec2 iUV;

out vec2 vUV;

uniform mat4 uTransform;
uniform mat4 uModel;

void main() {
  gl_Position = uTransform * uModel * vec4(iPosition, 1.0f);
  vUV = iUV;
}
