#ifndef __TERREATE_GRAPHICS_KERNEL_HPP__
#define __TERREATE_GRAPHICS_KERNEL_HPP__

// #include "buffer.hpp"
#include "defines.hpp"
#include "globj.hpp"

namespace TerreateGraphics::Compute {
using namespace TerreateGraphics::Defines;
// using namespace TerreateGraphics::Core;
using namespace TerreateGraphics::GL;
using namespace TerreateCore::Math;

class ComputeKernel final : public TerreateObjectBase {
private:
  Bool mCompiled = false;
  Bool mLinked = false;
  GLObject mKernelID = GLObject();
  Str mKernelSource = "";

public:
  /*
   * @brief: OpenGL compute shader wrapper class.
   */
  ComputeKernel();
  ~ComputeKernel() override;

  Uint GetID() const { return mKernelID; }

  /*
   * @brief: Get attribute index
   * @param: name: name of attribute
   * @return: attribute index
   */
  unsigned GetAttribute(Str const &name) const {
    return glGetAttribLocation(mKernelID, name.c_str());
  }
  /*
   * @brief: Getter for shader uniform ID.
   * @param: name: name of uniform
   * @return: uniform ID
   */
  unsigned GetLocation(Str const &name) const {
    return glGetUniformLocation(mKernelID, name.c_str());
  }
  /*
   * @brief: Getter for shader storage block index.
   * @param: name: name of storage block
   * @return: storage block index
   */
  unsigned GetStorageBlockIndex(Str const &name) const {
    return glGetProgramResourceIndex(mKernelID, GL_SHADER_STORAGE_BLOCK,
                                     name.c_str());
  }

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
  void SetBools(Str const &name, Bool const *value, Uint const &count) const;
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
  void SetInts(Str const &name, Int const *value, Uint const &count) const;
  /*
   * @brief: Setter for shader Int array uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetInts(Str const &name, Vec<Int> value) const;
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
  void SetFloats(Str const &name, Float const *value, Uint const &count) const;
  /*
   * @brief: Setter for shader float array uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetFloats(Str const &name, Vec<Float> value) const;
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
   * @brief: Setter for shader mat3 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat3(Str const &name, mat3 const &value) const;
  /*
   * @brief: Setter for shader mat4 uniform.
   * @param: name: name of uniform
   * @param: value: value of uniform
   */
  void SetMat4(Str const &name, mat4 const &value) const;

  /*
   * @brief: Add kernel source.
   * @param: source: source code to add
   */
  void AddKernelSource(Str const &source) { mKernelSource += source; }

  /*
   * @brief: This function binds storage block index to binding point.
   * @param: name: name of storage block
   * @param: binding: binding point
   */
  void BindStorageBlock(Str const &name, Uint const &binding) const {
    glShaderStorageBlockBinding(mKernelID, this->GetStorageBlockIndex(name),
                                binding);
  }

  /*
   * @brief: Compile shader.
   */
  void Compile();
  /*
   * @brief: Link shader.
   */
  void Link();
  /*
   * @brief: Dispatch compute shader.
   * @param: x: number of work groups in x direction
   */
  void Dispatch(Uint const &x) const { this->Dispatch(x, 1, 1); }
  /*
   * @brief: Dispatch compute shader.
   * @param: x: number of work groups in x direction
   * @param: y: number of work groups in y direction
   */
  void Dispatch(Uint const &x, Uint const &y) const { this->Dispatch(x, y, 1); }
  /*
   * @brief: Dispatch compute shader.
   * @param: x: number of work groups in x direction
   * @param: y: number of work groups in y direction
   * @param: z: number of work groups in z direction
   */
  void Dispatch(Uint const &x, Uint const &y, Uint const &z) const;

  operator Bool() const override { return mKernelID; }
};
} // namespace TerreateGraphics::Compute
#endif // __TERREATE_GRAPHICS_KERNEL_HPP__
