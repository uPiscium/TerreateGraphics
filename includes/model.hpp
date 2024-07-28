#ifndef __TERREATE_GRAPHICS_MODEL_HPP__
#define __TERREATE_GRAPHICS_MODEL_HPP__

#include "bitflag.hpp"
#include "buffer.hpp"
#include "defines.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Model {
using namespace TerreateGraphics::Defines;

using TextureMap = Shared<Core::Texture>;

class MaterialData : public Core::Object {
private:
  Str mName;
  Map<ColorProperty, vec4> mColorProperties;
  Map<FloatProperty, Float> mFloatProperties;
  Map<TextureProperty, TextureMap> mTextureProperties;

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
  TextureMap GetTextureProperty(TextureProperty const &property) const {
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
  void SetTextureProperty(TextureProperty const &property, TextureMap value);

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
  TextureMap operator[](TextureProperty const &property) const {
    return this->GetTextureProperty(property);
  }
};

class BufferConstructor {
private:
  BufferUsage mUsage;
  Map<ModelDataType, Vec<Vec<Float>>> mVertexProperties;
  std::pair<Vec<Vec<Float>>, Vec<Vec<Uint>>> mJointData;
  Vec<Vec<Vec<Uint>>> mFaces;
  Int mMaterial;
  Bool mGenNormals = false;

public:
  /*
   * @brief: This class constructs a Buffer object from vertex data sets.
   * @param: usage: Buffer usage.
  */
  BufferConstructor(BufferUsage const &usage = BufferUsage::STATIC_DRAW, Bool const &genNormals = false);
  ~BufferConstructor();

  /*
   * @brief: Load vertex position data.
   * @note: Data format => [[x1, y1, z1], [x2, y2, z2], ...]
   * @param: positions: Vertex position data.
  */
  void LoadPositions(Vec<Vec<Float>> const &positions);
  /*
   * @brief: Load vertex normal data. If you set "genNormals" parameter true, normals will generated automatically.
   * @note: Data format => [[x1, y1, z1], [x2, y2, z2], ...]
   * @param: normals: Vertex normal data.
  */
  void LoadNormals(Vec<Vec<Float>> const &normals);
  /*
   * @brief: Load vertex UV data.
   * @note: Data format => [[u1, v1], [u2, v2], ...]
   * @param: uvs: Vertex UV data.
  */
  void LoadUVs(Vec<Vec<Float>> const &uvs);
  /*
   * @brief: Load vertex color data.
   * @note: Data format => [[r1, g1, b1, a1], [r2, g2, b2, a2], ...]
   * @param: colors: Vertex color data.
  */
  void LoadColors(Vec<Vec<Float>> const &colors);
  /*
   * @brief: Load vertex joints' weight data.
   * @note: Data format => [[w11, w12, w13, w14], [w21, w22, w23, w24], ...]
   * @param: weights: Vertex joints' weight data.
  */
  void LoadJointWeights(Vec<Vec<Float>> const &weights);
  /*
   * @brief: Load vertex joint index data.
   * @note: Data format => [[j11, j12, j13, j14], [j21, j22, j23, j24], ...]
   * @param: joints: Vertex joint index data.
  */
  void LoadJointIndices(Vec<Vec<Uint>> const &joints);
  /*
   * @brief: Load vertex face data.
   * @note: Data format
   * [
   *   [
   *     [position_index, normal_index(optional), uv_index(optional), color_index(optional), joint_index(optional), weight_index(optional)],
   *     [...],
   *     ...
   *   ]
   * ]
   * @param: faces: Vertex face data.
  */
  void LoadFaces(Vec<Vec<Vec<Uint>>> const &faces);

  /*
   * @brief: Construct buffer data.
   * @param: buffer: Construct target.
  */
  void Construct(Buffer &buffer);
};

class MeshData {
private:
  BufferUsage mUsage;
  Core::BitFlag<ModelFlag> mFlag;
  Map<ModelFlag, Vec<Vec<Float>>> mVertexProperties;
  Vec<Vec<Uint>> mVertexSet;
  Vec<Float> mVertices;
  Vec<Uint> mIndices;
  Int mMaterial;

public:
  /*
   * @brief: This class stores mesh data of a model. Stored datas are buffer
   * usage, flags, vertex properties(or vertices), indices, and material index.
   * @param: usage: Buffer usage.
   */
  MeshData(BufferUsage const &usage = BufferUsage::STATIC_DRAW)
      : mUsage(usage), mMaterial(-1) {}
  ~MeshData() {}

  /*
   * @brief: Get the flag of the mesh data.
   * @return: Flag of the mesh data.
   */
  BufferUsage const &GetUsage() const { return mUsage; }
  /*
   * @brief: Get the flag of the mesh data.
   * @return: Flag of the mesh data.
   */
  ModelFlag GetFlag() const { return (ModelFlag)mFlag; }
  /*
   * @brief: Get the material index of the mesh data.
   * @return: Material index of the mesh data.
   */
  Int const &GetMaterial() const { return mMaterial; }
  /*
   * @brief: Get the indices of the mesh data.
   * @return: Indices of the mesh data.
   */
  Vec<Uint> const &GetIndices() const { return mIndices; }
  /*
   * @brief: Get the vertices of the mesh data.
   * @return: Vertices of the mesh data.
   */
  Vec<Float> const &AcquireVertices();

  /*
   * @brief: Set the flag of the mesh data.
   * @param: flag: Flag to set.
   */
  void SetFlag(ModelFlag const &flag) { mFlag.Set(flag); }

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

  /*
   * @brief: Load the flags of the mesh data.
   * @param: flags: Flags to load.
   */
  void LoadFlag(ModelFlag const &flags) { mFlag.Set(flags); }
  /*
   * @brief: Load the vertices of the mesh data.
   * @param: vertices: Vertices to load.
   */
  void LoadVertices(Vec<Float> const &vertices) { mVertices = vertices; }
  /*
   * @brief: Load the indices of the mesh data.
   * @param: indices: Indices to load.
   */
  void LoadIndices(Vec<Uint> const &indices) { mIndices = indices; }
  /*
   * @brief: Load the material index of the mesh data.
   * @param: material: Material index to load.
   */
  void LoadMaterial(Int const &material) { mMaterial = material; }

  /*
   * @brief: Load the vertex set data of the mesh data.
   * @param: sets: Face data to load.
   */
  void LoadVertexSet(Vec<Vec<Uint>> const &sets) { mVertexSet = sets; }
  /*
   * @brief: Load the position data of the mesh data.
   * @param: position: Position data to load.
   */
  void LoadPosition(Vec<Vec<Float>> const &position) {
    mVertexProperties[ModelFlag::POSITION] = position;
  }
  /*
   * @brief: Load the normal data of the mesh data.
   * @param: normal: Normal data to load.
   */
  void LoadNormal(Vec<Vec<Float>> const &normal);
  /*
   * @brief: Load the UV data of the mesh data.
   * @param: uv: UV data to load.
   */
  void LoadUV(Vec<Vec<Float>> const &uv);
  /*
   * @brief: Load the color data of the mesh data.
   * @param: color: Color data to load.
   */
  void LoadColor(Vec<Vec<Float>> const &color);
  /*
   * @brief: Load the joint data of the mesh data.
   * @param: joint: Joint data to load.
   */
  void LoadJoint(Vec<Vec<Float>> const &joint);
  /*
   * @brief: Load the weight data of the mesh data.
   * @param: weight: Weight data to load.
   */
  void LoadWeight(Vec<Vec<Float>> const &weight);
  /*
   * @brief: Load the morph data of the mesh data.
   * @param: morph: Morph data to load.
   */
  void LoadMorph(Vec<Vec<Float>> const &morph);

  /*
   * @brief: Construct buffer data of the mesh from the loaded vertex
   * properties.
   */
  void Construct();
};

class Mesh : public Core::Object {
private:
  BufferUsage mUsage;
  Core::BitFlag<ModelFlag> mFlag;
  Shared<Core::Buffer> mBuffer;
  Uint mMaterial;

public:
  /*
   * @brief: This class draws a mesh with material.
   */
  Mesh() : mBuffer(nullptr), mFlag(ModelFlag::EMPTY) {}
  /*
   * @brief: This class draws a mesh with material.
   * @param: data: Mesh data to draw.
   */
  Mesh(MeshData &data);
  Mesh(Mesh const &other)
      : mUsage(other.mUsage), mFlag(other.mFlag), mBuffer(other.mBuffer),
        mMaterial(other.mMaterial) {}
  ~Mesh() {}

  /*
   * @brief: Get the buffer usage.
   * @return: Buffer usage.
   */
  BufferUsage const &GetUsage() const { return mUsage; }
  /*
   * @brief: Get material index of the mesh.
   * @return: Material index of the mesh.
   */
  Uint const &GetMaterial() const { return mMaterial; }
  /*
   * @brief: Get the flag of the mesh.
   * @return: Flag of the mesh.
   */
  ModelFlag GetFlag() const { return (ModelFlag)mFlag; }

  /*
   * @brief: Load the data of the mesh.
   * @param: data: Mesh data to load.
   */
  void LoadData(MeshData &data);
  /*
   * @brief: Draw the mesh.
   * @note: Mesh data is assumed to be organized in triangles.
   */
  void Draw() const { mBuffer->Draw(DrawMode::TRIANGLES); }

  Mesh &operator=(Mesh const &other);

public:
  /*
   * @brief: Generate the attributes of the mesh from the flag.
   * @param: flag: Flag of the mesh.
   * @return: Attributes of the mesh.
   */
  static Vec<Core::Attribute> GenerateAttributes(ModelFlag const &flag);
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
} // namespace TerreateGraphics::Model

#endif // __TERREATE_GRAPHICS_MODEL_HPP__
