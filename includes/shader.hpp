#ifndef __TERREATE_GRAPHICS_SHADER_HPP__
#define __TERREATE_GRAPHICS_SHADER_HPP__

#include "defines.hpp"
#include "logger.hpp"
#include "object.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

struct ShaderOption {
  Bool blending = true;
  Bool culling = false;
  Bool depth = true;
  Bool scissor = false;
  Bool stencil = false;
  BlendingFuntion src = BlendingFuntion::ONE;
  BlendingFuntion dst = BlendingFuntion::ZERO;
  CullingFace cullFace = CullingFace::BACK;
  CullingMode frontFace = CullingMode::CCW;
  DepthFunction depthFunc = DepthFunction::LESS;
  StencilFunction stencilFunc = StencilFunction::ALWAYS;
  Int stencilRef = 0;
  Uint stencilMask = 0xFF;
  StencilOperation sFail = StencilOperation::KEEP;
  StencilOperation dpFail = StencilOperation::KEEP;
  StencilOperation dpPass = StencilOperation::KEEP;
};

class Shader final : public Object {
private:
  Bool mCompiled = false;
  ID mShaderID = 0;
  Str mVertexShaderSource = "";
  Str mFragmentShaderSource = "";
  Str mGeometryShaderSource = "";
  ShaderOption mOption;

public:
  /*
   * @brief: OpenGL shader wrapper class. This class handles vertex, fragment,
   * and geometry shaders.
   */
  Shader();
  ~Shader() override;

  /*
   * @brief: Getter for shader uniform ID.
   * @param: name: name of uniform
   * @return: uniform ID
   */
  unsigned GetLocation(Str const &name) const;

  /*
   * @brief: Setter for shader Bool uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetBool(Str const &name, Bool const &value) const;
  /*
   * @brief: Setter for shader Bool array uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   * @param: count: number of elements in array
   */
  void SetBools(Str const &name, Bool const *value, Int const &count) const;
  /*
   * @brief: Setter for shader Int uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetInt(Str const &name, Int const &value) const;
  /*
   * @brief: Setter for shader Int array uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   * @param: count: number of elements in array
   */
  void SetInts(Str const &name, Int const *value, Int const &count) const;
  /*
   * @brief: Setter for shader float uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetFloat(Str const &name, Float const &value) const;
  /*
   * @brief: Setter for shader float array uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   * @param: count: number of elements in array
   */
  void SetFloats(Str const &name, Float const *value, Int const &count) const;
  /*
   * @brief: Setter for shader vec2 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetVec2(Str const &name, vec2 const &value) const;
  /*
   * @brief: Setter for shader vec3 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetVec3(Str const &name, vec3 const &value) const;
  /*
   * @brief: Setter for shader vec4 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetVec4(Str const &name, vec4 const &value) const;
  /*
   * @brief: Setter for shader mat2 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat2(Str const &name, mat2 const &value) const;
  /*
   * @brief: Setter for shader mat2x3 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat2x3(Str const &name, mat2x3 const &value) const;
  /*
   * @brief: Setter for shader mat2x4 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat2x4(Str const &name, mat2x4 const &value) const;
  /*
   * @brief: Setter for shader mat3x2 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat3x2(Str const &name, mat3x2 const &value) const;
  /*
   * @brief: Setter for shader mat3 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat3(Str const &name, mat3 const &value) const;
  /*
   * @brief: Setter for shader mat3x4 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat3x4(Str const &name, mat3x4 const &value) const;
  /*
   * @brief: Setter for shader mat4x2 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat4x2(Str const &name, mat4x2 const &value) const;
  /*
   * @brief: Setter for shader mat4x3 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat4x3(Str const &name, mat4x3 const &value) const;
  /*
   * @brief: Setter for shader mat4 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat4(Str const &name, mat4 const &value) const;
  /*
   * @brief: Setter for blending function.
   * @param: src: source blending function
   * @param: dst: destination blending function
   */
  void SetBlending(BlendingFuntion const &src, BlendingFuntion const &dst);
  /*
   * @brief: Setter for culling face.
   * @param: face: face to cull
   */
  void SetCullingFace(CullingFace const &face,
                      CullingMode const &frontFace = CullingMode::CCW);
  /*
   * @brief: Setter for depth function.
   * @param: func: depth function
   */
  void SetDepth(DepthFunction const &func);
  /*
   * @brief: Setter for stencil function.
   * @param: func: stencil function
   */
  void SetStencilFunction(StencilFunction const &func, Int const &ref,
                          Uint const &mask);
  /*
   * @brief: Setter for stencil operation.
   * @param: sFail: stencil fail operation
   * @param: dpFail: stencil depth fail operation
   * @param: dpPass: stencil depth pass operation
   */
  void SetStencilOperation(StencilOperation const &sFail,
                           StencilOperation const &dpFail,
                           StencilOperation const &dpPass);

  /*
   * @brief: Add vertex shader source to current source.
   * @param: source: source code to add
   */
  void AddVertexShaderSource(Str const &source);
  /*
   * @brief: Add fragment shader source to current source.
   * @param: source: source code to add
   */
  void AddFragmentShaderSource(Str const &source);
  /*
   * @brief: Add geometry shader source to current source.
   * @param: source: source code to add
   */
  void AddGeometryShaderSource(Str const &source);
  /*
   * @brief: This function swiches blending on or off.
   * @param: value: true to turn on, false to turn off
   */
  void UseBlending(Bool const &value);
  /*
   * @brief: This function swiches culling on or off.
   * @param: value: true to turn on, false to turn off
   */
  void UseCulling(Bool const &value);
  /*
   * @brief: This function swiches depth testing on or off.
   * @param: value: true to turn on, false to turn off
   */
  void UseDepth(Bool const &value);
  /*
   * @brief: This function swiches scissor testing on or off.
   * @param: value: true to turn on, false to turn off
   */
  void UseScissor(Bool const &value);
  /*
   * @brief: This function swiches stencil testing on or off.
   * @param: value: true to turn on, false to turn off
   */
  void UseStencil(Bool const &value);
  /*
   * @brief: This function activates selected texture binding point.
   * @param: target: texture binding point
   */
  void ActiveTexture(TextureTargets const &target) const;
  /*
   * @brief: Compile shader.
   */
  void Compile();
  /*
   * @brief: Use shader.
   * @sa: Compile
   * @detail: This function should be called after shader is compiled.
   */
  void Use() const;
  /*
   * @brief: Unuse shader.
   */
  void Unuse() const;

  operator Bool() const override { return mShaderID != 0; }

public:
  /*
   * @brief: Load shader source from file.
   * @param: path: path to shader source file
   * @param: source: string to store source code
   * @return: source code
   */
  static Str LoadShaderSource(Str const &path);
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_SHADER_HPP__
