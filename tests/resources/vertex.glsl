#version 330 core
layout(location=0) in vec3 iPosition;
layout(location=1) in vec3 iNormal;
layout(location=2) in vec2 iUV;

out vec3 vNormal;
out vec2 vUV;

uniform mat3 uNormalTransform;
uniform mat4 uTransform;
uniform mat4 uModel;

void main() {
  // gl_Position = uTransform * uModel * vec4(iPosition, 1.0f);
  gl_Position = uModel * vec4(iPosition, 1.0f);
  vNormal = uNormalTransform * iNormal;
  vUV = iUV;
}
