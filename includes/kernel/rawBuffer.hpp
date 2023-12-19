#pragma once
#include "../defines.hpp"
#include "rawObject.hpp"

namespace GeoFrame {
class Attribute {
  private:
    size_t mIndex = 0;
    size_t mComps = 0;
    size_t mStride = 0;
    size_t mOffset = 0;

  public:
    /*
     * Attribute generator for OpenGL.
     * @param index: Index of this attribute.
     * @param comps: Number of components of this attribute.
     * @param offset: Offset of this attribute.
     */
    Attribute(size_t const &index, size_t const &comps, size_t const &stride,
              size_t const &offset)
        : mIndex(index), mComps(comps), mStride(stride), mOffset(offset) {}

    /*
     * @return: Index of this attribute.
     */
    size_t const &GetIndex() const { return mIndex; }
    /*
     * @return: Number of components of this attribute.
     */
    size_t const &GetComps() const { return mComps; }
    /*
     * @return: Size of stride of this attribute.
     */
    size_t const &GetStride() const { return mStride; }
    /*
     * @return: Offset from the beginning of this attributes.
     */
    size_t const &GetOffset() const { return mOffset; }

  public:
    /*
     * Generate attributes from component data. Offsets and indices are
     * calculated automatically.
     * @params comps: Component of each attribute.
     * @return: Attribute list.
     */
    static Vec<Attribute> GenerateAttributes(Vec<size_t> const &comps);
    /*
     * Generate attributes from component, offset, and index data.
     * @params comps: Component of each attribute.
     * @return: Attribute list.
     */
    static Vec<Attribute> GenerateAttributes(Vec<size_t> const &comps,
                                             Vec<size_t> const &offsets,
                                             Vec<size_t> const &strides);
};

namespace Kernel {
class RawBuffer : public RawObject {
  private:
    ID mVAO = 0;
    ID mVBO = 0;
    ID mIBO = 0;
    BufferUsage mUsage = BufferUsage::STATIC_DRAW;

    size_t mNumIndices = 0;

    bool mSetVBO = false;
    bool mSetIBO = false;

  public:
    M_DISABLE_COPY_AND_ASSIGN(RawBuffer);

  public:
    /*
     * OpenGL buffer wrapper class. This class handles vertex array, vertex
     * buffer, and element array.
     * @param usage: Usage of this buffer on OpenGL.
     */
    RawBuffer(BufferUsage usage);
    ~RawBuffer();

    /*
     * @return: VAO
     */
    ID const &GetVAO() const { return mVAO; }
    /*
     * @return: VBO
     */
    ID const &GetVBO() const { return mVBO; }
    /*
     * @return: IBO
     */
    ID const &GetIBO() const { return mIBO; }
    /*
     * @return: Buffer usage
     */
    BufferUsage const &GetUsage() const { return mUsage; }

    /*
     * Load vertex buffer data.
     * @param data: Pointer to vertex buffer data to be loaded.
     * @param size: Size of data to be loaded.
     */
    void LoadVertices(float const *data, size_t const &size);
    /*
     * Load vertex buffer data.
     * @param data: Vector of vertex buffer data to be loaded.
     */
    void LoadVertices(Vec<float> const &data) {
        this->LoadVertices(data.data(), data.size() * sizeof(float));
    }
    /*
     * Load index buffer data.
     * @param data: Pointer to index buffer data to be loaded.
     * @param size: Size of data to be loaded.
     */
    void LoadIndices(unsigned const *data, size_t const &size);
    /*
     * Load index buffer data.
     * @param data: Vector of index buffer data to be loaded.
     */
    void LoadIndices(Vec<unsigned> const &data) {
        this->LoadIndices(data.data(), data.size() * sizeof(Index));
    }
    /*
     * Load vertex attributes.
     * @param data: Pointer to attribute data to be loaded.
     * @param size: Size of data to be loaded.
     */
    void LoadAttributes(Attribute const *data, size_t const &size);
    /*
     * Load vertex attributes.
     * @param data: Vector of attribute data to be loaded.
     */
    void LoadAttributes(Vec<Attribute> const &data) {
        this->LoadAttributes(data.data(), data.size());
    }

    /*
     * Draw registered buffer.
     * @param drawMode: Draw mode of opengl.
     */
    void Draw(DrawMode const &drawMode);
    /*
     * Draw registered buffer more than once.
     * @param numInstances: Number of instances to draw.
     * @param drawMode: Draw mode of opengl.
     */
    void DrawInstances(size_t const &numInstances, DrawMode const &drawMode);
};
} // namespace Kernel
} // namespace GeoFrame
