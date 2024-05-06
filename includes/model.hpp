#ifndef __TC_MODEL_HPP__
#define __TC_MODEL_HPP__

#include "bitflag.hpp"
#include "buffer.hpp"
#include "defines.hpp"
#include "math/math.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace TerreateCore::Model {
using namespace TerreateCore::Defines;

using TexMap = Shared<Core::Texture>;

class MaterialData : public Core::Object {
private:
  Str mName;
  Map<ColorProperty, vec4> mColorProperties;
  Map<FloatProperty, Float> mFloatProperties;
  Map<TextureProperty, TexMap> mTextureProperties;

public:
  /*
   * @brief: MaterialData class stores material datas for a model.
   * This class stores the name of the material, color properties, float
   * properties, and texture properties.
   */
  MaterialData() {}
  ~MaterialData() {}

  /*
   * @brief: Get the name of the material.
   * @return: The name of the material.
   */
  Str const &GetName() const { return mName; }
  /*
   * @brief: Get the color property of the material.
   * @param: property: The color property to get.
   * @throw: If the color property does not exist, throw an out_of_range error.
   * @return: The color property.
   */
  vec4 const &GetColorProperty(ColorProperty const &property) const {
    return mColorProperties.at(property);
  }
  /*
   * @brief: Get the float property of the material.
   * @param: property: The float property to get.
   * @throw: If the float property does not exist, throw an out_of_range error.
   * @return: The float property.
   */
  Float const &GetFloatProperty(FloatProperty const &property) const {
    return mFloatProperties.at(property);
  }
  /*
   * @brief: Get the texture property of the material.
   * @param: property: The texture property to get.
   * @throw: If the texture property does not exist, throw an out_of_range
   * error.
   * @return: The texture property.
   */
  TexMap GetTextureProperty(TextureProperty const &property) const {
    return mTextureProperties.at(property);
  }

  /*
   * @brief: Set the name of the material.
   * @param: name: The name of the material.
   */
  void SetName(Str const &name) { mName = name; }
  /*
   * @brief: Set the color property of the material.
   * @param: property: The color property to set.
   * @param: value: The color property.
   */
  void SetColorProperty(ColorProperty const &property, vec4 const &value);
  /*
   * @brief: Set the float property of the material.
   * @param: property: The float property to set.
   * @param: value: The float property.
   */
  void SetFloatProperty(FloatProperty const &property, Float const &value);
  /*
   * @brief: Set the texture property of the material.
   * @param: property: The texture property to set.
   * @param: value: The texture property.
   */
  void SetTextureProperty(TextureProperty const &property, TexMap value);

  /*
   * @brief: Check if the material has a color property.
   * @param: property: The color property to check.
   * @return: True if the material has the color property, false otherwise.
   */
  bool HasColorProperty(ColorProperty const &property) const {
    return mColorProperties.find(property) != mColorProperties.end();
  }
  /*
   * @brief: Check if the material has a float property.
   * @param: property: The float property to check.
   * @return: True if the material has the float property, false otherwise.
   */
  bool HasFloatProperty(FloatProperty const &property) const {
    return mFloatProperties.find(property) != mFloatProperties.end();
  }
  /*
   * @brief: Check if the material has a texture property.
   * @param: property: The texture property to check.
   * @return: True if the material has the texture property, false otherwise.
   */
  bool HasTextureProperty(TextureProperty const &property) const {
    return mTextureProperties.find(property) != mTextureProperties.end();
  }

  /*
   * @brief: Remove the color property from the material.
   * @param: property: The color property to remove.
   * @throw: If the color property does not exist, throw an out_of_range error.
   */
  void RemoveColorProperty(ColorProperty const &property);
  /*
   * @brief: Remove the float property from the material.
   * @param: property: The float property to remove.
   * @throw: If the float property does not exist, throw an out_of_range error.
   */
  void RemoveFloatProperty(FloatProperty const &property);
  /*
   * @brief: Remove the texture property from the material.
   * @param: property: The texture property to remove.
   * @throw: If the texture property does not exist, throw an out_of_range
   * error.
   */
  void RemoveTextureProperty(TextureProperty const &property);

  /*
   * @brief: Clear the color properties of the material.
   */
  void ClearColorProperties() { mColorProperties.clear(); }
  /*
   * @brief: Clear the float properties of the material.
   */
  void ClearFloatProperties() { mFloatProperties.clear(); }
  /*
   * @brief: Clear the texture properties of the material.
   */
  void ClearTextureProperties() { mTextureProperties.clear(); }

  vec4 const &operator[](ColorProperty const &property) const {
    return this->GetColorProperty(property);
  }
  Float const &operator[](FloatProperty const &property) const {
    return this->GetFloatProperty(property);
  }
  TexMap operator[](TextureProperty const &property) const {
    return this->GetTextureProperty(property);
  }
};

class MeshData {
private:
  Core::BitFlag<ModelFlag> mFlag;
  Vec<Float> mVertices;
  Vec<Uint> mIndices;
  Int mMaterial;

public:
  MeshData() {}
  ~MeshData() {}

  /*
   * @brief: Get the flag of the mesh data.
   * @return: Flag of the mesh data.
   */
  ModelFlag GetFlag() const { return (ModelFlag)mFlag; }
  /*
   * @brief: Get the vertices of the mesh data.
   * @return: Vertices of the mesh data.
   */
  Vec<Float> const &GetVertices() const { return mVertices; }
  /*
   * @brief: Get the indices of the mesh data.
   * @return: Indices of the mesh data.
   */
  Vec<Uint> const &GetIndices() const { return mIndices; }
  /*
   * @brief: Get the material index of the mesh data.
   * @return: Material index of the mesh data.
   */
  Int const &GetMaterial() const { return mMaterial; }

  /*
   * @brief: Set the flag of the mesh data.
   * @param: flag: Flag to set.
   */
  void SetFlag(ModelFlag const &flag) { mFlag.Set(flag); }
  /*
   * @brief: Set the vertices of the mesh data.
   * @param: vertices: Vertices to set.
   */
  void SetVertices(Vec<Float> const &vertices) { mVertices = vertices; }
  /*
   * @brief: Set the indices of the mesh data.
   * @param: indices: Indices to set.
   */
  void SetIndices(Vec<Uint> const &indices) { mIndices = indices; }
  /*
   * @brief: Set the material index of the mesh data.
   * @param: material: Material index to set.
   */
  void SetMaterial(Uint const &material) { mMaterial = material; }

  /*
   * @brief: Check if the mesh data has normals.
   * @return: True if the mesh data has normals, false otherwise.
   */
  Bool HasNormals() const { return mFlag & ModelFlag::NORMAL; }
  /*
   * @brief: Check if the mesh data has UVs.
   * @return: True if the mesh data has UVs, false otherwise.
   */
  Bool HasUVs() const { return mFlag & ModelFlag::UV; }
  /*
   * @brief: Check if the mesh data has colors.
   * @return: True if the mesh data has colors, false otherwise.
   */
  Bool HasColors() const { return mFlag & ModelFlag::COLOR; }
  /*
   * @brief: Check if the mesh data has joints.
   * @return: True if the mesh data has joints, false otherwise.
   */
  Bool HasJoint() const { return mFlag & ModelFlag::JOINT; }
  /*
   * @brief: Check if the mesh data has weights.
   * @return: True if the mesh data has weights, false otherwise.
   */
  Bool HasWeight() const { return mFlag & ModelFlag::WEIGHT; }
  /*
   * @brief: Check if the mesh data has material.
   * @return: True if the mesh data has material, false otherwise.
   */
  Bool HasMaterial() const { return mFlag & ModelFlag::MATERIAL; }
  /*
   * @brief: Check if the mesh data has morph.
   * @return: True if the mesh data has morph, false otherwise.
   */
  Bool HasMorph() const { return mFlag & ModelFlag::MORPH; }
};

class Mesh : public Core::Object {
private:
  Shared<Core::Buffer> mBuffer;
  Uint mMaterial;

public:
  /*
   * @brief: This class draws a mesh with material.
   * @param: data: Mesh data to draw.
   */
  Mesh(MeshData const &data);
  Mesh(Mesh const &other)
      : mBuffer(other.mBuffer), mMaterial(other.mMaterial) {}
  ~Mesh() {}

  /*
   * @brief: Get the raw buffer of the mesh.
   * @return: Raw buffer data of the mesh.
   */
  Shared<Core::Buffer> GetBuffer() const { return mBuffer; }
  /*
   * @brief: Get the material index of the mesh.
   * @return: Material index of the mesh.
   */
  Uint const &GetMaterial() const { return mMaterial; }

  /*
   * @brief: Draw the mesh.
   * @note: Mesh data is assumed to be organized in triangles.
   */
  void Draw() const { mBuffer->Draw(DrawMode::TRIANGLES); }

  Mesh &operator=(Mesh const &other);

public:
  static Vec<Core::Attribute> GetAttributes(ModelFlag const &flag);
};

class Model : public Core::Object {
private:
  Vec<Mesh> mMeshes;
  Vec<MaterialData> mMaterials;

public:
  /*
   * @brief: This class manages the meshes and material datas of the model.
   */
  Model() {}
  ~Model() {}

  /*
   * @brief: Get the mesh datas of the model.
   * @return: Mesh datas of the model.
   */
  Vec<Mesh> const &GetMeshes() const { return mMeshes; }
  /*
   * @brief: Get the material datas of the model.
   * @return: Material datas of the model.
   */
  Vec<MaterialData> const &GetMaterials() const { return mMaterials; }

  /*
   * @brief: Add mesh data to the model.
   * @param: mesh: Mesh data to add.
   */
  void AddMesh(Mesh const &mesh) { mMeshes.push_back(mesh); }
  /*
   * @brief: Add mateiral data to the model.
   * @return: material: Material data to add.
   */
  void AddMaterial(MaterialData const &material) {
    mMaterials.push_back(material);
  }

  /*
   * @brief: Draw the meshes of the model.
   * @note: Mesh data is assumed to be organized in triangles.
   */
  void Draw() const;

  Model &operator=(Model const &other);
};
} // namespace TerreateCore::Model

#endif // __TC_MODEL_HPP__
