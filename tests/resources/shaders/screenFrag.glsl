#version 430 core
out vec4 fragColor[4];

void main() {
  fragColor[0] = vec4(1.0, 0.0, 0.0, 1.0);
  fragColor[1] = vec4(0.0, 1.0, 0.0, 1.0);
  fragColor[2] = vec4(0.0, 0.0, 1.0, 1.0);
  fragColor[3] = vec4(1.0, 1.0, 1.0, 1.0);
}
