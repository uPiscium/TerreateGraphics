#version 430 core
in vec3 iPosition;
in vec2 iUV;
in vec3 iColor;

out vec3 vNormal;
out vec2 vUV;
out vec3 vColor;

layout(std140) uniform Matrices {
  mat4 uTransform;
  mat4 uModel;
  mat4 uView;
  mat4 uProjection;
};

void main() {
  gl_Position = uProjection * uView * uTransform * uModel * vec4(iPosition, 1.0f);
  vNormal = vec3(0.0f, 0.0f, 0.0f);
  vUV = iUV;
  vColor = iColor;
}
