#include "../../includes/kernel/rawBuffer.hpp"

namespace GeoFrame {
Vec<Attribute> Attribute::GenerateAttributes(Vec<size_t> const &comps) {
    Vec<Attribute> attributes;
    size_t stride = 0;
    for (size_t i = 0; i < comps.size(); ++i) {
        stride += comps[i] * sizeof(float);
    }
    size_t offset = 0;
    for (size_t i = 0; i < comps.size(); ++i) {
        attributes.push_back(Attribute(i, comps[i], stride, offset));
        offset += comps[i] * sizeof(float);
    }
    return attributes;
}

Vec<Attribute> Attribute::GenerateAttributes(Vec<size_t> const &comps,
                                             Vec<size_t> const &offsets,
                                             Vec<size_t> const &strides) {
    Vec<Attribute> attributes;
    for (size_t i = 0; i < comps.size(); ++i) {
        attributes.push_back(Attribute(i, comps[i], strides[i], offsets[i]));
    }
    return attributes;
}

namespace Kernel {
RawBuffer::RawBuffer(BufferUsage usage) : mUsage(usage) {
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mIBO);
}

RawBuffer::~RawBuffer() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mIBO);
}

void RawBuffer::LoadVertices(float const *data, size_t const &size) {
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    if (mSetVBO) {
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    } else {
        glBufferData(GL_ARRAY_BUFFER, size, data, (unsigned)mUsage);
        mSetVBO = true;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RawBuffer::LoadIndices(unsigned const *data, size_t const &size) {
    mNumIndices = size / sizeof(Index);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    if (mSetIBO) {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    } else {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, (unsigned)mUsage);
        mSetIBO = true;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RawBuffer::LoadAttributes(Attribute const *attributes,
                               size_t const &size) {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    for (size_t i = 0; i < size; ++i) {
        Attribute const &attr = attributes[i];
        glEnableVertexAttribArray(attr.GetIndex());
        glVertexAttribPointer(attr.GetIndex(), attr.GetComps(), GL_FLOAT,
                              GL_FALSE, attr.GetStride(),
                              (void *)(attr.GetOffset()));
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RawBuffer::Draw(DrawMode const &drawMode) {
    glBindVertexArray(mVAO);
    if (mNumIndices == 0) {
        M_GEO_THROW(KernelError, "No indices loaded.");
    }
    glDrawElements((unsigned)drawMode, mNumIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RawBuffer::DrawInstances(size_t const &numInstances,
                              DrawMode const &drawMode) {
    glBindVertexArray(mVAO);
    if (mNumIndices == 0) {
        M_GEO_THROW(KernelError, "No indices loaded.");
    }
    glDrawElementsInstanced((unsigned)drawMode, mNumIndices, GL_UNSIGNED_INT, 0,
                            numInstances);
    glBindVertexArray(0);
}
} // namespace Kernel
} // namespace GeoFrame
