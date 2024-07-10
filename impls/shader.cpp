#include "../includes/shader.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

Str GetShaderLog(Uint const &id) {
  Int status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status) {
    return "";
  }

  char log[1024];
  glGetShaderInfoLog(id, 1024, NULL, log);
  return log;
}

void CheckCompileStatus(Uint const &id, Str const &name) {
  Str log = GetShaderLog(id);
  if (log != "") {
    log = name + " shader log: " + log;
    Logger::Error(log.c_str());
    return;
  }
}

Str GetProgramLog(Uint const &id) {
  Int status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);

  if (status) {
    return "";
  }

  char log[1024];
  glGetProgramInfoLog(id, 1024, NULL, log);
  return log;
}

void CheckLinkStatus(Uint const &id) {
  Str log = GetProgramLog(id);

  if (log != "") {
    log = "Shader program log: " + log;
    Logger::Error(log.c_str());
    return;
  }
}

Shader::Shader() {
  Logger::Trace(LOCATION(Shader));

  mShaderID = glCreateProgram();
  mCompiled = false;
  Logger::Debug("Shader is generated.");
}

Shader::~Shader() {
  Logger::Trace(LOCATION(Shader));

  glDeleteProgram(mShaderID);
  Logger::Debug("Shader is deleted.");
}

unsigned Shader::GetLocation(const Str &name) const {
  Logger::Trace(LOCATION(Shader));

  return glGetUniformLocation(mShaderID, name.c_str());
}

void Shader::SetBool(const Str &name, Bool const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1i(this->GetLocation(name), (Int)value);
}

void Shader::SetBools(const Str &name, Bool const *value,
                      Int const &count) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1iv(this->GetLocation(name), count, (Int *)value);
}

void Shader::SetInt(const Str &name, Int const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1i(this->GetLocation(name), value);
}

void Shader::SetInts(const Str &name, Int const *value,
                     Int const &count) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1iv(this->GetLocation(name), count, value);
}

void Shader::SetFloat(const Str &name, Float const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1f(this->GetLocation(name), value);
}

void Shader::SetFloats(const Str &name, Float const *value,
                       Int const &count) const {
  Logger::Trace(LOCATION(Shader));

  glUniform1fv(this->GetLocation(name), count, value);
}

void Shader::SetVec2(const Str &name, vec2 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform2fv(this->GetLocation(name), 1, value.GetArray());
}

void Shader::SetVec3(const Str &name, vec3 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform3fv(this->GetLocation(name), 1, value.GetArray());
}

void Shader::SetVec4(const Str &name, vec4 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniform4fv(this->GetLocation(name), 1, value.GetArray());
}

void Shader::SetMat2(const Str &name, mat2 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix2fv(this->GetLocation(name), 1, GL_FALSE,
                     value.AcquireTransposed().GetArray());
}

void Shader::SetMat2x3(const Str &name, mat2x3 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix2x3fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat2x4(const Str &name, mat2x4 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix2x4fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat3x2(const Str &name, mat3x2 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix3x2fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat3(const Str &name, mat3 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix3fv(this->GetLocation(name), 1, GL_FALSE,
                     value.AcquireTransposed().GetArray());
}

void Shader::SetMat3x4(const Str &name, mat3x4 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix3x4fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat4x2(const Str &name, mat4x2 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix4x2fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat4x3(const Str &name, mat4x3 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix4x3fv(this->GetLocation(name), 1, GL_FALSE,
                       value.AcquireTransposed().GetArray());
}

void Shader::SetMat4(const Str &name, mat4 const &value) const {
  Logger::Trace(LOCATION(Shader));

  glUniformMatrix4fv(this->GetLocation(name), 1, GL_FALSE,
                     value.AcquireTransposed().GetArray());
}

void Shader::SetBlending(BlendingFuntion const &src,
                         BlendingFuntion const &dst) {
  Logger::Trace(LOCATION(Shader));

  mOption.src = src;
  mOption.dst = dst;
}

void Shader::SetCullingFace(CullingFace const &face,
                            CullingMode const &frontFace) {
  Logger::Trace(LOCATION(Shader));

  mOption.cullFace = face;
  mOption.frontFace = frontFace;
}

void Shader::SetStencilFunction(StencilFunction const &func, int const &ref,
                                Uint const &mask) {
  Logger::Trace(LOCATION(Shader));

  mOption.stencilFunc = func;
  mOption.stencilRef = ref;
  mOption.stencilMask = mask;
}

void Shader::SetStencilOperation(StencilOperation const &sFail,
                                 StencilOperation const &dpFail,
                                 StencilOperation const &dpPass) {
  Logger::Trace(LOCATION(Shader));

  mOption.sFail = sFail;
  mOption.dpFail = dpFail;
  mOption.dpPass = dpPass;
}

void Shader::AddVertexShaderSource(const Str &source) {
  Logger::Trace(LOCATION(Shader));

  mVertexShaderSource += source;
}

void Shader::AddFragmentShaderSource(const Str &source) {
  Logger::Trace(LOCATION(Shader));

  mFragmentShaderSource += source;
}

void Shader::AddGeometryShaderSource(const Str &source) {
  Logger::Trace(LOCATION(Shader));

  mGeometryShaderSource += source;
}

void Shader::UseBlending(Bool const &value) {
  Logger::Trace(LOCATION(Shader));

  mOption.blending = value;
}

void Shader::UseCulling(Bool const &value) {
  Logger::Trace(LOCATION(Shader));

  mOption.culling = value;
}

void Shader::UseDepth(Bool const &value) {
  Logger::Trace(LOCATION(Shader));

  mOption.depth = value;
}

void Shader::UseScissor(Bool const &value) {
  Logger::Trace(LOCATION(Shader));

  mOption.scissor = value;
}

void Shader::UseStencil(Bool const &value) {
  Logger::Trace(LOCATION(Shader));

  mOption.stencil = value;
}

void Shader::Compile() {
  Logger::Trace(LOCATION(Shader));

  if (mVertexShaderSource == "") {
    Logger::Error("Vertex shader source is empty");
    return;
  }

  if (mFragmentShaderSource == "") {
    Logger::Error("Fragment shader source is empty");
    return;
  }

  ID vertID = 0;
  vertID = glCreateShader(GL_VERTEX_SHADER);
  char const *vertSource = mVertexShaderSource.c_str();
  glShaderSource(vertID, 1, &vertSource, NULL);
  glCompileShader(vertID);
  CheckCompileStatus(vertID, "Vertex");

  ID fragID = 0;
  fragID = glCreateShader(GL_FRAGMENT_SHADER);
  char const *fragSource = mFragmentShaderSource.c_str();
  glShaderSource(fragID, 1, &fragSource, NULL);
  glCompileShader(fragID);
  CheckCompileStatus(fragID, "Fragment");

  glAttachShader(mShaderID, vertID);
  glAttachShader(mShaderID, fragID);

  if (mGeometryShaderSource != "") {
    ID geomID = 0;
    geomID = glCreateShader(GL_GEOMETRY_SHADER);
    char const *geomSource = mGeometryShaderSource.c_str();
    glShaderSource(geomID, 1, &geomSource, NULL);
    glCompileShader(geomID);
    CheckCompileStatus(geomID, "Geometry");

    glAttachShader(mShaderID, geomID);
  }

  glLinkProgram(mShaderID);
  CheckLinkStatus(mShaderID);

  mCompiled = true;
}

Str Shader::LoadShaderSource(const Str &path) {
  Logger::Trace(LOCATION(Shader));

  InputFileStream file;
  file.open(path.c_str());

  if (!file.is_open()) {
    Logger::Error("Failed to open shader source file");
    return "";
  }

  std::stringstream stream;
  stream << file.rdbuf();
  file.close();

  return stream.str();
}

void Shader::ActiveTexture(TextureTargets const &target) const {
  Logger::Trace(LOCATION(Shader));

  this->Use();
  glActiveTexture((GLenum)target);
}

void Shader::Use() const {
  Logger::Trace(LOCATION(Shader));

  if (!mCompiled) {
    Logger::Error("Shader is not compiled");
    return;
  }

  glUseProgram(mShaderID);

  if (mOption.blending) {
    glEnable(GL_BLEND);
    glBlendFunc((GLenum)mOption.src, (GLenum)mOption.dst);
  } else {
    glDisable(GL_BLEND);
  }

  if (mOption.depth) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc((GLenum)mOption.depthFunc);
  } else {
    glDisable(GL_DEPTH_TEST);
  }

  if (mOption.stencil) {
    glEnable(GL_STENCIL_TEST);
    glStencilFunc((GLenum)mOption.stencilFunc, mOption.stencilRef,
                  mOption.stencilMask);
    glStencilOp((GLenum)mOption.sFail, (GLenum)mOption.dpFail,
                (GLenum)mOption.dpPass);
  } else {
    glDisable(GL_STENCIL_TEST);
  }

  if (mOption.scissor) {
    glEnable(GL_SCISSOR_TEST);
  } else {
    glDisable(GL_SCISSOR_TEST);
  }

  if (mOption.culling) {
    glEnable(GL_CULL_FACE);
    glCullFace((GLenum)mOption.cullFace);
    glFrontFace((GLenum)mOption.frontFace);
  } else {
    glDisable(GL_CULL_FACE);
  }
}

void Shader::Unuse() const {
  Logger::Trace(LOCATION(Shader));

  glUseProgram(0);
}
} // namespace TerreateCore::Core
