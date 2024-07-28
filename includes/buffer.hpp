#ifndef __TERREATE_CORE_BUFFER_HPP__
#define __TERREATE_CORE_BUFFER_HPP__

#include "defines.hpp"
#include "logger.hpp"
#include "object.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

class Attribute {
private:
  Ulong mIndex = 0;
  Ulong mComps = 0;
  Ulong mStride = 0;
  Ulong mOffset = 0;

public:
  /*
   * Attribute generator for OpenGL.
   * @param index: Index of this attribute.
   * @param comps: Number of components of this attribute.
   * @param offset: Offset of this attribute.
   */
  Attribute(Ulong const &index, Ulong const &comps, Ulong const &stride,
            Ulong const &offset);

  /*
   * @return: Index of this attribute.
   */
  Ulong const &GetIndex() const;
  /*
   * @return: Number of components of this attribute.
   */
  Ulong const &GetComps() const;
  /*
   * @return: Size of stride of this attribute.
   */
  Ulong const &GetStride() const;
  /*
   * @return: Offset from the beginning of this attributes.
   */
  Ulong const &GetOffset() const;

public:
  /*
   * Generate attributes from component data. Offsets and indices are
   * calculated automatically.
   * @params comps: Component of each attribute.
   * @return: Attribute list.
   */
  static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps);
  /*
   * Generate attributes from component, offset, and index data.
   * @params comps: Component of each attribute.
   * @return: Attribute list.
   */
  static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps,
                                           Vec<Ulong> const &offsets,
                                           Vec<Ulong> const &strides);
};

class Buffer final : public Object {
private:
  ID mVAO = 0;
  ID mVBO = 0;
  ID mIBO = 0;
  BufferUsage mUsage = BufferUsage::STATIC_DRAW;

  Ulong mNumIndices = 0;

  Bool mSetVBO = false;
  Bool mSetIBO = false;

public:
  TC_DISABLE_COPY_AND_ASSIGN(Buffer);

public:
  /*
   * @brief: OpenGL buffer wrapper class. This class handles vertex array,
   * vertex buffer, and element array.
   * @param: usage: Usage of this buffer on OpenGL.
   */
  Buffer(BufferUsage usage);
  ~Buffer() override;

  /*
   * @brief: Get buffer usage on opengl.
   * @return: Buffer usage
   */
  BufferUsage const &GetUsage() const;

  /*
   * @brief: Load vertex buffer data.
   * @param: data: Pointer to vertex buffer data to be loaded.
   * @param: size: Size of data to be loaded.
   */
  void LoadVertices(Float const *data, Size const &size);
  /*
   * @brief: Load vertex buffer data.
   * @param data: Vector of vertex buffer data to be loaded.
   */
  void LoadVertices(Vec<Float> const &data) {
    this->LoadVertices(data.data(), data.size() * sizeof(Float));
  }
  /*
   * @brief: Load index buffer data.
   * @param: data: Pointer to index buffer data to be loaded.
   * @param: size: Size of data to be loaded.
   */
  void LoadIndices(Uint const *data, Size const &size);
  /*
   * @brief: Load index buffer data.
   * @param: data: Vector of index buffer data to be loaded.
   */
  void LoadIndices(Vec<Uint> const &data) {
    this->LoadIndices(data.data(), data.size() * sizeof(Uint));
  }
  /*
   * @brief: Load vertex attributes.
   * @param: data: Pointer to attribute data to be loaded.
   * @param: size: Size of data to be loaded.
   */
  void LoadAttributes(Attribute const *data, Size const &size);
  /*
   * @brief: Load vertex attributes.
   * @param: data: Vector of attribute data to be loaded.
   */
  void LoadAttributes(Vec<Attribute> const &data) {
    this->LoadAttributes(data.data(), data.size());
  }

  /*
   * @brief: Draw registered buffer.
   * @param: drawMode: Draw mode of opengl.
   */
  void Draw(DrawMode const &drawMode);
  /*
   * @brief: Draw registered buffer more than once.
   * @param: numInstances: Number of instances to draw.
   * @param: drawMode: Draw mode of opengl.
   */
  void DrawInstances(Size const &numInstances, DrawMode const &drawMode);

  operator Bool() const override { return mVAO != 0 && mVBO != 0 && mIBO != 0; }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_CORE_BUFFER_HPP__
