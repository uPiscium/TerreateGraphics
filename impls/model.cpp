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
                                      TextureMap value) {
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
    Logger::Error("Color property not found");
  }
}

void MaterialData::RemoveFloatProperty(FloatProperty const &property) {
  if (this->HasFloatProperty(property)) {
    mFloatProperties.erase(property);
  } else {
    Logger::Error("Float property not found");
  }
}

void MaterialData::RemoveTextureProperty(TextureProperty const &property) {
  if (this->HasTextureProperty(property)) {
    mTextureProperties.erase(property);
  } else {
    Logger::Error("Texture property not found");
  }
}

Vec<Float> const &MeshData::AcquireVertices() {
  if (mVertexProperties.empty()) {
    return mVertices;
  }

  this->Construct();
  return mVertices;
}

void MeshData::LoadNormal(Vec<Vec<Float>> const &normal) {
  mVertexProperties.insert({ModelFlag::NORMAL, normal});
  this->SetFlag(ModelFlag::NORMAL);
}

void MeshData::LoadUV(Vec<Vec<Float>> const &uv) {
  mVertexProperties.insert({ModelFlag::UV, uv});
  this->SetFlag(ModelFlag::UV);
}

void MeshData::LoadColor(Vec<Vec<Float>> const &color) {
  mVertexProperties.insert({ModelFlag::COLOR, color});
  this->SetFlag(ModelFlag::COLOR);
}

void MeshData::LoadJoint(Vec<Vec<Float>> const &joint) {
  mVertexProperties.insert({ModelFlag::JOINT, joint});
  this->SetFlag(ModelFlag::JOINT);
}

void MeshData::LoadWeight(Vec<Vec<Float>> const &weight) {
  mVertexProperties.insert({ModelFlag::WEIGHT, weight});
  this->SetFlag(ModelFlag::WEIGHT);
}

void MeshData::LoadMorph(Vec<Vec<Float>> const &morph) {
  mVertexProperties.insert({ModelFlag::MORPH, morph});
  this->SetFlag(ModelFlag::MORPH);
}

void MeshData::Construct() {
  Vec<Vec<Vec<Float>>> properties;
  mVertices.clear();

  if (mVertexProperties.find(ModelFlag::POSITION) == mVertexProperties.end()) {
    Logger::Error("Position property not found");
  }

  properties.push_back(mVertexProperties[ModelFlag::POSITION]);

  if (mVertexProperties.find(ModelFlag::NORMAL) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::NORMAL]);
  }

  if (mVertexProperties.find(ModelFlag::UV) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::UV]);
  }

  if (mVertexProperties.find(ModelFlag::COLOR) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::COLOR]);
  }

  if (mVertexProperties.find(ModelFlag::JOINT) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::JOINT]);
  }

  if (mVertexProperties.find(ModelFlag::WEIGHT) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::WEIGHT]);
  }

  if (mVertexProperties.find(ModelFlag::MORPH) != mVertexProperties.end()) {
    properties.push_back(mVertexProperties[ModelFlag::MORPH]);
  }

  if (properties.size() != mVertexSet[0].size()) {
    Logger::Error("Property size does not match vertex set size");
  }

  for (auto &set : mVertexSet) {
    for (Ulong i = 0; i < set.size(); ++i) {
      auto &property = properties[i];
      auto &comp = property[set[i]];
      mVertices.insert(mVertices.end(), comp.begin(), comp.end());
    }
  }
}

Mesh::Mesh(MeshData &data) : mMaterial(data.GetMaterial()) {
  mBuffer = std::make_shared<Core::Buffer>(data.GetUsage());
  mBuffer->LoadVertices(data.AcquireVertices());
  mBuffer->LoadAttributes(Mesh::GenerateAttributes(data.GetFlag()));
  mBuffer->LoadIndices(data.GetIndices());
}

void Mesh::LoadData(MeshData &data) {
  if (mFlag == ModelFlag::EMPTY) {
    mFlag = data.GetFlag();
  }

  if (data.GetFlag() != mFlag) {
    Logger::Error("Flag does not match");
  }

  if (mBuffer == nullptr) {
    mBuffer = std::make_shared<Core::Buffer>(data.GetUsage());
  }

  mBuffer->LoadVertices(data.AcquireVertices());
  mBuffer->LoadAttributes(Mesh::GenerateAttributes(data.GetFlag()));
  mBuffer->LoadIndices(data.GetIndices());
  mMaterial = data.GetMaterial();
}

Mesh &Mesh::operator=(Mesh const &other) {
  mUsage = other.mUsage;
  mFlag = other.mFlag;
  mBuffer = other.mBuffer;
  mMaterial = other.mMaterial;
  return *this;
}

Vec<Core::Attribute> Mesh::GenerateAttributes(ModelFlag const &flag) {
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
