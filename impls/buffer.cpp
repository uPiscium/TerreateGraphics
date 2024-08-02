#include "../includes/buffer.hpp"
#include "../includes/exceptions.hpp"
#include "TerreateCore/defines.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

Vec<Attribute> Attribute::GenerateAttributes(Vec<Ulong> const &comps) {
  Vec<Attribute> attributes;
  Ulong stride = 0;
  for (Ulong i = 0; i < comps.size(); ++i) {
    stride += comps[i] * sizeof(Float);
  }

  Ulong offset = 0;
  for (Ulong i = 0; i < comps.size(); ++i) {
    attributes.push_back(Attribute(i, comps[i], stride, offset));
    offset += comps[i] * sizeof(Float);
  }
  return attributes;
}

Vec<Attribute> Attribute::GenerateAttributes(Vec<Ulong> const &comps,
                                             Vec<Ulong> const &offsets,
                                             Vec<Ulong> const &strides) {
  Vec<Attribute> attributes;
  for (Ulong i = 0; i < comps.size(); ++i) {
    attributes.push_back(Attribute(i, comps[i], strides[i], offsets[i]));
  }
  return attributes;
}

Buffer::Buffer(BufferUsage usage) : mUsage(usage) {
  glGenVertexArrays(1, mVAO);
  glGenBuffers(1, mVBO);
  glGenBuffers(1, mIBO);
}

Buffer::~Buffer() {
  glDeleteVertexArrays(1, mVAO);
  glDeleteBuffers(1, mVBO);
  glDeleteBuffers(1, mIBO);
  mVAO.Delete();
  mVBO.Delete();
  mIBO.Delete();
}

void Buffer::LoadVertices(Float const *data, Size const &size) {
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  if (mSetVBO) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  } else {
    glBufferData(GL_ARRAY_BUFFER, size, data, (GLenum)mUsage);
    mSetVBO = true;
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::LoadIndices(Uint const *data, Size const &size) {
  mNumIndices = size / sizeof(Uint);
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
  if (mSetIBO) {
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
  } else {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, (GLenum)mUsage);
    mSetIBO = true;
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::LoadAttributes(Attribute const *attributes, Size const &size) {
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  for (Size i = 0; i < size; ++i) {
    Attribute const &attr = attributes[i];
    glEnableVertexAttribArray(attr.GetIndex());
    glVertexAttribPointer(attr.GetIndex(), attr.GetComps(), GL_FLOAT, GL_FALSE,
                          attr.GetStride(), (void const *)(attr.GetOffset()));
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::Draw(DrawMode const &drawMode) {
  glBindVertexArray(mVAO);
  if (mNumIndices == 0) {
    throw Exceptions::BufferError("No indices loaded.");
    return;
  }
  glDrawElements((GLenum)drawMode, mNumIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Buffer::DrawInstances(size_t const &numInstances,
                           DrawMode const &drawMode) {
  glBindVertexArray(mVAO);
  if (mNumIndices == 0) {
    throw Exceptions::BufferError("No indices loaded.");
    return;
  }

  glDrawElementsInstanced((GLenum)drawMode, mNumIndices, GL_UNSIGNED_INT, 0,
                          numInstances);
  glBindVertexArray(0);
}
} // namespace TerreateGraphics::Core
