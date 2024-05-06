#include "../includes/model.hpp"
#include <memory>

namespace TerreateCore::Model {
using namespace TerreateCore::Defines;
using namespace TerreateCore::Core;

void MaterialData::SetColorProperty(ColorProperty const &property,
                                    vec4 const &value) {
  if (this->HasColorProperty(property)) {
    mColorProperties[property] = value;
  } else {
    mColorProperties.insert({property, value});
  }
}

void MaterialData::SetFloatProperty(FloatProperty const &property,
                                    Float const &value) {
  if (this->HasFloatProperty(property)) {
    mFloatProperties[property] = value;
  } else {
    mFloatProperties.insert({property, value});
  }
}

void MaterialData::SetTextureProperty(TextureProperty const &property,
                                      TexMap value) {
  if (this->HasTextureProperty(property)) {
    mTextureProperties[property] = value;
  } else {
    mTextureProperties.insert({property, value});
  }
}

void MaterialData::RemoveColorProperty(ColorProperty const &property) {
  if (this->HasColorProperty(property)) {
    mColorProperties.erase(property);
  } else {
    TC_THROW("Color property not found");
  }
}

void MaterialData::RemoveFloatProperty(FloatProperty const &property) {
  if (this->HasFloatProperty(property)) {
    mFloatProperties.erase(property);
  } else {
    TC_THROW("Float property not found");
  }
}

void MaterialData::RemoveTextureProperty(TextureProperty const &property) {
  if (this->HasTextureProperty(property)) {
    mTextureProperties.erase(property);
  } else {
    TC_THROW("Texture property not found");
  }
}

Mesh::Mesh(MeshData const &data) : mMaterial(data.GetMaterial()) {
  mBuffer = std::make_shared<Core::Buffer>(BufferUsage::STATIC_DRAW);
  mBuffer->LoadVertices(data.GetVertices());
  auto attributes = Mesh::GetAttributes(data.GetFlag());
  mBuffer->LoadAttributes(Mesh::GetAttributes(data.GetFlag()));
  mBuffer->LoadIndices(data.GetIndices());
}

Mesh &Mesh::operator=(Mesh const &other) {
  mBuffer = other.mBuffer;
  mMaterial = other.mMaterial;
  return *this;
}

Vec<Core::Attribute> Mesh::GetAttributes(ModelFlag const &flag) {
  Vec<Ulong> attributes;
  attributes.push_back(3); // Position (x, y, z)

  if (flag & ModelFlag::NORMAL) {
    attributes.push_back(3); // Normals (x, y, z)
  }
  if (flag & ModelFlag::UV) {
    attributes.push_back(2); // UVs (u, v)
  }
  if (flag & ModelFlag::COLOR) {
    attributes.push_back(4); // Color (r, g, b, a)
  }
  if (flag & ModelFlag::JOINT) {
    attributes.push_back(4); // Joint (j1, j2, j3, j4)
  }
  if (flag & ModelFlag::WEIGHT) {
    attributes.push_back(4); // Weight (w1, w2, w3, w4)
  }
  if (flag & ModelFlag::MORPH) {
    attributes.push_back(3); // Morph (m1, m2, m3)
  }

  return Core::Attribute::GenerateAttributes(attributes);
}

void Model::Draw() const {
  for (auto &mesh : mMeshes) {
    mesh.Draw();
  }
}

Model &Model::operator=(Model const &other) {
  mMeshes = other.mMeshes;
  return *this;
}
} // namespace TerreateCore::Model
