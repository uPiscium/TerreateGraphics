#ifndef __TERREATE_GRAPHICS_BUFFER_HPP__
#define __TERREATE_GRAPHICS_BUFFER_HPP__

#include "compute.hpp"
#include "defines.hpp"
#include "exceptions.hpp"
#include "globj.hpp"
#include "shader.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::Compute;
using namespace TerreateGraphics::GL;

struct AttributeData {
  Ulong vboIndex;
  Ulong index;
  Ulong size;
  Ulong stride;
  Ulong offset;
};

class BufferDataConstructor {
private:
  Vec<Vec<Vec<Float>>> mVertexDataComponents;
  Vec<Vec<Uint>> mVertexIndices;
  Vec<Str> mAttributeNames;
  Map<Str, AttributeData> mAttributes;
  Vec<Float> mVertexData;
  Bool mConstructed = false;
  Bool mUpdated = false;
  Uint mOffset = 0u;

public:
  /*
   * @brief: Construct a new BufferDataConstructor object. BufferDataConstructor
   * is used to construct data for a new buffer object
   */
  BufferDataConstructor() {}
  ~BufferDataConstructor() {}

  /*
   * @brief: Get attribute names
   * @return: Attribute names
   */
  Vec<Str> const &GetAttributeNames() const { return mAttributeNames; }
  /*
   * @brief: Get attributes
   * @return: Attributes
   */
  Map<Str, AttributeData> const &GetAttributes() const { return mAttributes; }
  /*
   * @brief: Get vertex data
   * @return: Vertex data
   */
  Vec<Float> const &GetVertexData() const;

  /*
   * @brief: Set vertex indices
   * @detail: Indices are used to construct each vertex data from vertex
   * component data
   * @param: indices: Indices to set
   */
  void SetVertexIndices(Vec<Vec<Uint>> const &indices) {
    mVertexIndices = indices;
  }

  /*
   * @brief: Add a vertex component to the buffer data constructor
   * @param: name: Name of the vertex component
   * @param: data: Data of the vertex component
   */
  void AddVertexComponent(Str const &name, Vec<Vec<Float>> const &data);
  /*
   * @brief: Reload a vertex component in the buffer data constructor
   * @param: name: Name of the vertex component
   * @param: data: Data of the vertex component
   */
  void ReloadVertexComponent(Str const &name, Vec<Vec<Float>> const &data);
  /*
   * @brief: Construct the buffer data
   */
  void Construct();
};

class Buffer : public TerreateObjectBase {
private:
  GLObject mVAO = GLObject();
  GLObject mIBO = GLObject();
  Ulong mIndexCount = 0u;
  Bool mLoadedIndices = false;
  Vec<GLObject> mBuffers;
  Map<Str, AttributeData> mAttributes;

public:
  /*
   * @brief: Construct a new Buffer object
   */
  Buffer() { glGenVertexArrays(1, mVAO); }
  ~Buffer() override;

  /*
   * @brief: Set vertex attribute divisor
   * @param: attribute: Attribute to set divisor
   * @param: divisor: Divisor value
   */
  void SetAttributeDivisor(AttributeData const &attribute,
                           Uint const &divisor) const;
  /*
   * @brief: Set vertex attribute divisor
   * @param: name: Name of the attribute to set divisor
   * @param: divisor: Divisor value
   */
  void SetAttributeDivisor(Str const &name, Uint const &divisor) const {
    this->SetAttributeDivisor(mAttributes.at(name), divisor);
  }

  /*
   * @brief: Load data into the new buffer
   * @param: shader: Shader to use to draw the buffer
   * @param: raw: Raw data to load
   * @param: attrs: Attributes to load
   * @param: usage: Buffer usage
   */
  void LoadData(Shader &shader, Vec<Float> const &raw,
                Map<Str, AttributeData> const &attrs,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW);
  /*
   * @brief: Load data into the new buffer
   * @param: shader: Shader to use to draw the buffer
   * @param: bdc: Buffer data constructor object
   * @param: usage: Buffer usage
   */
  void LoadData(Shader &shader, BufferDataConstructor const &bdc,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW);
  /*
   * @brief: Reload data into the buffer
   * @param: target: Target buffer
   * @param: bdc: Buffer data constructor object
   */
  void ReloadData(AttributeData const &target,
                  BufferDataConstructor const &bdc);
  /*
   * @brief: Reload data into the buffer
   * @param: name: Name of the attribute to reload
   * @param: bdc: Buffer data constructor object
   */
  void ReloadData(Str const &name, BufferDataConstructor const &bdc) {
    this->ReloadData(mAttributes.at(name), bdc);
  }
  /*
   * @brief: Reload data into the buffer
   * @param: target: Target buffer
   * @param: bdc: Buffer data constructor object
   * @param: offset: Offset to reload data
   */
  void ReloadData(AttributeData const &target, BufferDataConstructor const &bdc,
                  Uint const &offset);
  /*
   * @brief: Reload data into the buffer
   * @param: name: Name of the attribute to reload
   * @param: bdc: Buffer data constructor object
   * @param: offset: Offset to reload data
   */
  void ReloadData(Str const &name, BufferDataConstructor const &bdc,
                  Uint const &offset) {
    this->ReloadData(mAttributes.at(name), bdc, offset);
  }
  /*
   * @brief: Load indices into the buffer
   * @param: indices: Indices to load
   */
  void LoadIndices(Vec<Uint> const &indices);
  /*
   * @brief: Load indices into the buffer
   * @param: indices: Indices to load
   */
  void LoadIndices(Vec<Vec<Uint>> const &indices) {
    this->LoadIndices(Buffer::Flatten(indices));
  }
  /*
   * @brief: Reload indices into the buffer
   * @param: indices: Indices to reload
   */
  void ReloadIndices(Vec<Uint> const &indices);
  /*
   * @brief: Reload indices into the buffer
   * @param: indices: Indices to reload
   */
  void ReloadIndices(Vec<Vec<Uint>> const &indices) {
    this->ReloadIndices(Buffer::Flatten(indices));
  }
  /*
   * @brief: Bind the buffer
   */
  void Bind() const { glBindVertexArray(mVAO); }
  /*
   * @brief: Unbind the buffer
   */
  void Unbind() const { glBindVertexArray(0); }
  /*
   * @brief: Draw the buffer
   * @param: mode: Mode to draw
   */
  void Draw(DrawMode const &mode) const;
  /*
   * @brief: Draw the buffer
   * @param: mode: Mode to draw
   * @param: count: Number of instances to draw
   */
  void Draw(DrawMode const &mode, Ulong const &count) const;

  AttributeData &operator[](Str const &name) { return mAttributes[name]; }
  AttributeData &operator[](char const *name) { return mAttributes[name]; }
  AttributeData const &operator[](Str const &name) const {
    return mAttributes.at(name);
  }
  AttributeData const &operator[](char const *name) const {
    return mAttributes.at(name);
  }

public:
  /*
   * @brief: Flatten a 2D vector into a 1D vector
   * @param: data: Data to flatten
   * @return: Flattened data
   */
  template <typename T> static Vec<T> Flatten(Vec<Vec<T>> const &data) {
    Vec<T> flat;
    for (auto const &v : data) {
      flat.insert(flat.end(), v.begin(), v.end());
    }
    return flat;
  }
};

class UniformBuffer : public TerreateObjectBase {
private:
  GLObject mUBO = GLObject();

private:
  void Bind() const { glBindBuffer(GL_UNIFORM_BUFFER, mUBO); }
  void Unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

public:
  UniformBuffer() { glGenBuffers(1, mUBO); }
  ~UniformBuffer() override;

  template <typename T>
  void LoadData(T const &data,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW) {
    this->Bind();
    glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &data, (GLenum)usage);
    this->Unbind();
  }
  template <typename T>
  void LoadData(Vec<T> const &data,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW) {
    this->Bind();
    glBufferData(GL_UNIFORM_BUFFER, data.size() * sizeof(T), data.data(),
                 (GLenum)usage);
    this->Unbind();
  }
  template <typename T>
  void ReloadData(T const &data, Ulong const &offset = 0u) {
    this->Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), &data);
    this->Unbind();
  }
  template <typename T>
  void ReloadData(Vec<T> const &data, Ulong const &offset = 0u) {
    this->Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, data.size() * sizeof(T),
                    data.data());
    this->Unbind();
  }
  void Allocate(Ulong const &size,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW);

  void Bind(Shader const &shader, Str const &name) const;
};

class ShaderStorageBuffer : public TerreateObjectBase {
private:
  GLObject mSSBO = GLObject();
  Size mSize = 0u;

private:
  void Bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBO); }
  void Unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }

public:
  ShaderStorageBuffer() { glGenBuffers(1, mSSBO); }
  ~ShaderStorageBuffer() override;

  Size const &GetSize() const { return mSize; }
  template <typename T> void GetData(T &data, Ulong const &offset = 0u) const {
    if (mSize == 0u) {
      return;
    }

    if (mSize > sizeof(T)) {
      throw Exceptions::BufferError("Data size is too small.");
    }

    this->Bind();
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, mSize, &data);
    this->Unbind();
  }
  template <typename T>
  void GetData(Vec<T> &data, Ulong const &offset = 0u) const {
    if (mSize == 0u) {
      return;
    }

    if (mSize % sizeof(T) != 0) {
      throw Exceptions::BufferError("Data size is not a multiple of T.");
    }

    data.resize(mSize / sizeof(T));
    this->Bind();
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, mSize, data.data());
    this->Unbind();
  }

  template <typename T>
  void LoadData(T const &data,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW) {
    this->Bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T), &data, (GLenum)usage);
    mSize = sizeof(T);
    this->Unbind();
  }
  template <typename T>
  void LoadData(Vec<T> const &data,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW) {
    this->Bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(),
                 (GLenum)usage);
    mSize = data.size() * sizeof(T);
    this->Unbind();
  }
  template <typename T>
  void ReloadData(T const &data, Ulong const &offset = 0u) {
    this->Bind();
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(T), &data);
    mSize = sizeof(T);
    this->Unbind();
  }
  template <typename T>
  void ReloadData(Vec<T> const &data, Ulong const &offset = 0u) {
    this->Bind();
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, data.size() * sizeof(T),
                    data.data());
    mSize = data.size() * sizeof(T);
    this->Unbind();
  }

  void Allocate(Ulong const &size,
                BufferUsage const &usage = BufferUsage::STATIC_DRAW);
  void Bind(Shader &shader, Str const &name) const;
  void Bind(ComputeKernel &kernel, Str const &name) const;
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_BUFFER_HPP__
