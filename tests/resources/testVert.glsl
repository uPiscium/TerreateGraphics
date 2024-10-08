#version 330 core
in vec3 iPosition;
in vec2 iUV;
in vec3 iColor;
// layout(location=1) in vec3 iNormal;

out vec3 vNormal;
out vec2 vUV;
out vec3 vColor;

// uniform mat4 uNormalTransform;
// uniform mat4 uTransform;
// uniform mat4 uModel;

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
