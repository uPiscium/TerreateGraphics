#include "../includes/shader.hpp"

namespace GeoFrame {
Tag Shader::sTag = ResourceBase::sTag + Tag("Shader");

Str GetShaderLog(unsigned const &id) {
  int status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status) {
    return "";
  }

  char log[1024];
  glGetShaderInfoLog(id, 1024, NULL, log);
  return log;
}

void CheckCompileStatus(unsigned const &id, Str const &name) {
  Str log = GetShaderLog(id);
  if (log != "") {
    log = name + " shader log: " + log;
    M_GEO_THROW(KernelError, log.c_str());
  }
}

Str GetProgramLog(unsigned const &id) {
  int status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);

  if (status) {
    return "";
  }

  char log[1024];
  glGetProgramInfoLog(id, 1024, NULL, log);
  return log;
}

void CheckLinkStatus(unsigned const &id) {
  Str log = GetProgramLog(id);

  if (log != "") {
    log = "Shader program log: " + log;
    M_GEO_THROW(KernelError, log.c_str());
  }
}

void Shader::Compile() {
  if (mVertexShaderSource == "") {
    M_GEO_THROW(KernelError, "Vertex shader source is empty");
    return;
  }

  if (mFragmentShaderSource == "") {
    M_GEO_THROW(KernelError, "Fragment shader source is empty");
    return;
  }

  unsigned vertID = 0;
  vertID = glCreateShader(GL_VERTEX_SHADER);
  char const *vertSource = mVertexShaderSource.c_str();
  glShaderSource(vertID, 1, &vertSource, NULL);
  glCompileShader(vertID);
  CheckCompileStatus(vertID, "Vertex");

  unsigned fragID = 0;
  fragID = glCreateShader(GL_FRAGMENT_SHADER);
  char const *fragSource = mFragmentShaderSource.c_str();
  glShaderSource(fragID, 1, &fragSource, NULL);
  glCompileShader(fragID);
  CheckCompileStatus(fragID, "Fragment");

  glAttachShader(mShaderID, vertID);
  glAttachShader(mShaderID, fragID);

  if (mGeometryShaderSource != "") {
    unsigned geomID = 0;
    geomID = glCreateShader(GL_GEOMETRY_SHADER);
    char const *geomSource = mGeometryShaderSource.c_str();
    glShaderSource(geomID, 1, &geomSource, NULL);
    glCompileShader(geomID);
    CheckCompileStatus(geomID, "Geometry");

    glAttachShader(mShaderID, geomID);
  }

  glLinkProgram(mShaderID);
  CheckLinkStatus(mShaderID);
}

Str Shader::LoadShaderSource(const Str &path) {
  std::ifstream file;
  file.open(path.c_str());

  if (!file.is_open()) {
    M_GEO_THROW(KernelError, "Failed to open shader source file");
    return "";
  }

  std::stringstream stream;
  stream << file.rdbuf();
  file.close();

  return stream.str();
}

void Shader::ActiveTexture(TextureTargets const &target) const {
  this->Use();
  glActiveTexture((GLenum)target);
}
} // namespace GeoFrame
