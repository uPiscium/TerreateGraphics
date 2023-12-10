#pragma once
#include "../defines.hpp"
#include "rawObject.hpp"

namespace GeoFrame {
class Attribute {
  private:
    size_t mIndex = 0;
    size_t mComps = 0;
    size_t mOffset = 0;

  public:
    /*
     * Attribute generator for OpenGL.
     * @param index: Index of this attribute.
     * @param comps: Number of components of this attribute.
     * @param offset: Offset of this attribute.
     */
    Attribute(size_t index, size_t comps, size_t offset)
        : mIndex(index), mComps(comps), mOffset(offset) {}

    /*
     * @return: Index of this attribute.
     */
    size_t const &GetIndex() const { return mIndex; }
    /*
     * @return: Number of components of this attribute.
     */
    size_t const &GetNComps() const { return mComps; }
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
     * Generate attributes from component and offset data. Indices is
     * calculated automatically.
     * @params comps: Component of each attribute.
     * @return: Attribute list.
     */
    static Vec<Attribute> GenerateAttributes(Vec<size_t> const &comps,
                                             Vec<size_t> const &offsets);
    /*
     * Generate attributes from component, offset, and index data.
     * @params comps: Component of each attribute.
     * @return: Attribute list.
     */
    static Vec<Attribute> GenerateAttributes(Vec<size_t> const &comps,
                                             Vec<size_t> const &offsets,
                                             Vec<size_t> const &indices);
};

namespace Kernel {
class RawBuffer : public RawObject {
  private:
    ID mVAO = 0;
    ID mVBO = 0;
    ID mIBO = 0;
    BufferUsage mUsage = BufferUsage::STATIC_DRAW;
    BufferType mType = BufferType::ARRAY_BUFFER;

  public:
    M_DISABLE_COPY_AND_ASSIGN(RawBuffer);

  public:
    /*
     * @param type: Type of this buffer on OpenGL.
     * @param usage: Usage of this buffer on OpenGL.
     */
    RawBuffer(BufferType type, BufferUsage usage);
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
     * @return: Buffer type
     */
    BufferType const &GetType() const { return mType; }

    /*
     * @param data: Pointer to vertex buffer data to be loaded.
     * @param size: Size of data to be loaded.
     */
    void LoadVertices(float const *data, size_t size);
    /*
     * @param data: Vector of vertex buffer data to be loaded.
     */
    void LoadVertices(Vec<float> const &data);
    /*
     * @param data: Pointer to index buffer data to be loaded.
     * @param size: Size of data to be loaded.
     */
    void LoadIndices(Index const *data, size_t size);
    /*
     * @param data: Vector of index buffer data to be loaded.
     */
    void LoadIndices(Vec<Index> const &data);
    void LoadAttributes();

    /*
     * @param buffer: Buffer to be copied.
     */
    void Copy(RawBuffer const &buffer) const;
};
} // namespace Kernel
} // namespace GeoFrame
