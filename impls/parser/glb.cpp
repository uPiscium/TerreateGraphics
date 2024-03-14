#include "../../includes/parser/glb.hpp"

namespace GeoFrame {
namespace Parser {
ObjectID const GLBParser::sOID = ObjectID("GLB_PARSER");

Bool GLBParser::ParsePBRMaterial(JsonNode &node,
                                 PBRMetallicRoughness &material) {
  if (!node.IsObject()) {
    return false;
  }

  JsonNode baseColorTexture;
  if (this->AcquireObject(
          node, "baseColorTexture",
          &baseColorTexture)) { // materials[i].pbrMetallicRoughness.baseColorTexture
    if (!this->AcquireUint(
            baseColorTexture, "index",
            &material
                 .baseColorTexture)) { // materials[i].pbrMetallicRoughness.baseColorTexture.index
      return false;
    }
  }

  Vec<Float> baseColorFactor;
  if (!this->AcquireArray(
          node, "baseColorFactor",
          &baseColorFactor)) { // materials[i].pbrMetallicRoughness.baseColorFactor
    baseColorFactor = Vec<Float>({0, 0, 0, 0});
  } else {
    if (baseColorFactor.size() != 4) {
      return false;
    }
    material.baseColorFactor = vec4(baseColorFactor[0], baseColorFactor[1],
                                    baseColorFactor[2], baseColorFactor[3]);
  }

  if (!this->AcquireNumber(
          node, "metallicFactor",
          &material
               .metallicFactor)) { // materials[i].pbrMetallicRoughness.metallicFactor
    material.metallicFactor = 0;
  }

  if (!this->AcquireNumber(
          node, "roughnessFactor",
          &material
               .roughnessFactor)) { // materials[i].pbrMetallicRoughness.roughnessFactor
    material.roughnessFactor = 0;
  }

  return true;
}

Bool GLBParser::ParseAttribute(JsonNode &node, GLBAttribute &attr) {
  if (!this->AcquireUint(node, "POSITION",
                         &attr.position)) { // attributes.POSITION
    return false;
  }

  if (!this->AcquireInt(node, "NORMAL", &attr.normal)) { // attributes.NORMAL
    attr.normal = -1;
  }

  for (int i = 0;; ++i) {
    Str texCoordName = "TEXCOORD_" + std::to_string(i);
    Uint texCoord = 0;
    if (!this->AcquireUint(node, texCoordName, &texCoord)) {
      break;
    }
    attr.texCoord.push_back(texCoord);
  }

  for (int i = 0;; ++i) {
    Str colorName = "COLOR_" + std::to_string(i);
    Vec<Float> color;
    if (!this->AcquireArray(node, colorName, &color)) {
      break;
    }
    if (color.size() != 4) {
      return false;
    }
    attr.color.push_back(vec4(color[0], color[1], color[2], color[3]));
  }

  for (int i = 0;; ++i) {
    Str jointName = "JOINTS_" + std::to_string(i);
    Uint joint = 0;
    if (!this->AcquireUint(node, jointName, &joint)) {
      break;
    }
    attr.joint.push_back(joint);
  }

  for (int i = 0;; ++i) {
    Str weightName = "WEIGHTS_" + std::to_string(i);
    Uint weight = 0;
    if (!this->AcquireUint(node, weightName, &weight)) {
      break;
    }
    attr.weight.push_back(weight);
  }

  return true;
}

Bool GLBParser::AcquireBool(JsonNode &node, Str const &key, Bool *value) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode boolean = node[key.c_str()]; // node.key
  if (!boolean.IsBool()) {
    return false;
  }
  *value = boolean.GetBool();
  return true;
}

Bool GLBParser::AcquireNumber(JsonNode &node, Str const &key, Float *value) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode number = node[key.c_str()]; // node.key
  if (!number.IsNumber()) {
    return false;
  }
  *value = number.GetNumber();
  return true;
}

Bool GLBParser::AcquireInt(JsonNode &node, Str const &key, Int *value) {
  Float number;
  if (!this->AcquireNumber(node, key, &number)) {
    return false;
  }
  *value = static_cast<Int>(number);
  return true;
}

Bool GLBParser::AcquireUint(JsonNode &node, Str const &key, Uint *value) {
  Float number;
  if (!this->AcquireNumber(node, key, &number)) {
    return false;
  }
  *value = static_cast<Uint>(number);
  return true;
}

Bool GLBParser::AcquireArray(JsonNode &node, Str const &key, Vec<Bool> *array) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode arr = node[key.c_str()]; // node.key
  if (!arr.IsArray()) {
    return false;
  }
  Vec<JsonNode> boolArray = arr.GetArray();
  for (auto &b : boolArray) {
    if (!b.IsBool()) {
      return false;
    }
    array->push_back(b.GetBool());
  }
  return true;
}

Bool GLBParser::AcquireArray(JsonNode &node, Str const &key,
                             Vec<Float> *array) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode arr = node[key.c_str()]; // node.key
  if (!arr.IsArray()) {
    return false;
  }
  Vec<JsonNode> floatArray = arr.GetArray();
  for (auto &f : floatArray) {
    if (!f.IsNumber()) {
      return false;
    }
    array->push_back(f.GetNumber());
  }
  return true;
}

Bool GLBParser::AcquireArray(JsonNode &node, Str const &key, Vec<Uint> *array) {
  Vec<Float> floatArray;
  if (!this->AcquireArray(node, key, &floatArray)) {
    return false;
  }
  for (auto &f : floatArray) {
    array->push_back(static_cast<Uint>(f));
  }
  return true;
}

Bool GLBParser::AcquireArray(JsonNode &node, Str const &key, Vec<Str> *array) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode arr = node[key.c_str()]; // node.key
  if (!arr.IsArray()) {
    return false;
  }
  Vec<JsonNode> strArray = arr.GetArray();
  for (auto &s : strArray) {
    if (!s.IsString()) {
      return false;
    }
    array->push_back(s.GetString());
  }
  return true;
}

Bool GLBParser::AcquireArray(JsonNode &node, Str const &key,
                             Vec<JsonNode> *array) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode arr = node[key.c_str()]; // node.key
  if (!arr.IsArray()) {
    return false;
  }
  *array = arr.GetArray();
  return true;
}

Bool GLBParser::AcquireString(JsonNode &node, Str const &key, Str *value) {
  if (!node.Has(key)) {
    return false;
  }
  JsonNode str = node[key.c_str()]; // node.key
  if (!str.IsString()) {
    return false;
  }
  *value = str.GetString();
  return true;
}

Bool GLBParser::AcquireObject(JsonNode &node, Str const &key,
                              JsonNode *object) {
  if (!node.Has(key)) {
    return false;
  }
  *object = node[key.c_str()]; // node.key
  if (!object->IsObject()) {
    return false;
  }
  return true;
}

Bool GLBParser::ParseHeader() {
  Byte header[20];
  mBuffer->Read(header, 20);
  if (M_MEMCMP(header, "glTF", 4) != 0) {
    return false;
  }
  GFu32 const version = *(GFu32 *)(header + 4);
  GFu32 const filesize = *(GFu32 *)(header + 8);
  GFu32 const jsonLength = *(GFu32 *)(header + 12);
  if (M_MEMCMP(header + 16, "JSON", 4) != 0) {
    return false;
  };
  Byte *rawJson = new Byte[jsonLength + 1];
  mBuffer->Read((Byte *)rawJson, jsonLength);
  rawJson[jsonLength] = '\0';
  Stream json;
  json << rawJson;
  Str jsonStr = json.str();
  Shared<IOBuffer> jsonBuffer =
      std::make_shared<IOBuffer>(jsonStr.begin(), jsonStr.end());
  delete[] rawJson;
  JsonParser parser(jsonBuffer, 10);
  if (!parser.Parse()) {
    return false;
  }
  mJsonData = parser.GetNode();
  return true;
}

Bool GLBParser::ParseAsset() {
  JsonNode asset = mJsonData["asset"]; // asset
  if (!this->AcquireObject(mJsonData, "asset", &asset)) {
    return false;
  }

  Str version;
  if (!this->AcquireString(asset, "version", &version)) { // asset.version
    mVersion = "2.0";
  } else {
    mVersion = version;
  }

  Str generator;
  if (!this->AcquireString(asset, "generator", &generator)) { // asset.generator
    mGenerator = "N/A";
  } else {
    mGenerator = generator;
  }

  Vec<Str> extensions;
  if (!this->AcquireArray(asset, "extensions",
                          &extensions)) { // asset.extensions
    mExtensions = Vec<Str>();
  } else {
    mExtensions = extensions;
  }

  return true;
}

Bool GLBParser::ParseScene() {
  Float scene;
  if (!this->AcquireNumber(mJsonData, "scene", &scene)) { // scene
    return false;
  }
  Uint sceneIndex = static_cast<Uint>(scene);

  Vec<JsonNode> scenesArray;
  if (!this->AcquireArray(mJsonData, "scenes", &scenesArray)) { // scenes
    return false;
  }

  for (int i = 0; i < scenesArray.size(); ++i) {
    JsonNode &scene = scenesArray[i];
    if (!scene.IsObject()) {
      return false;
    }

    GLBScene data;
    if (!this->AcquireString(scene, "name", &data.name)) { // scenes[i].name
      data.name = "N/A" + std::to_string(i);
    }

    if (!this->AcquireArray(scene, "nodes", &data.nodes)) { // scenes[i].nodes
      return false;
    }

    mScenes.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseNodes() {
  Vec<JsonNode> nodesArray; // nodes
  if (!this->AcquireArray(mJsonData, "nodes", &nodesArray)) {
    return false;
  }

  for (auto &node : nodesArray) {
    if (!node.IsObject()) {
      return false;
    }

    GLBNode data;
    if (!this->AcquireString(node, "name", &data.name)) { // nodes[i].name
      return false;
    }

    if (!this->AcquireArray(node, "children",
                            &data.children)) { // nodes[i].children
      data.children = Vec<Uint>();
    }

    Vec<Float> quaternion; // nodes[i].rotation
    if (!this->AcquireArray(node, "rotation", &quaternion)) {
      data.rotation = Quaternion(1, 0, 1, 0);
    } else {
      if (quaternion.size() != 4) {
        return false;
      }
      data.rotation = Quaternion(quaternion[3], quaternion[0], quaternion[1],
                                 quaternion[2]);
    }

    Vec<Float> translation; // nodes[i].translation
    if (!this->AcquireArray(node, "translation", &translation)) {
      data.translation = vec3(0, 0, 0);
    } else {
      if (translation.size() != 3) {
        return false;
      }
      data.translation = vec3(translation[0], translation[1], translation[2]);
    }

    Vec<Float> scale; // nodes[i].scale
    if (!this->AcquireArray(node, "scale", &scale)) {
      data.scale = vec3(1, 1, 1);
    } else {
      if (scale.size() != 3) {
        return false;
      }
      data.scale = vec3(scale[0], scale[1], scale[2]);
    }

    if (!this->AcquireUint(node, "mesh", &data.mesh)) { // nodes[i].mesh
      data.mesh = 0;
    }

    if (!this->AcquireUint(node, "skin", &data.skin)) { // nodes[i].skin
      data.skin = 0;
    }

    mNodes.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseMaterials() {
  Vec<JsonNode> materialsArray; // materials
  if (!this->AcquireArray(mJsonData, "materials", &materialsArray)) {
    return false;
  }

  for (int i = 0; i < materialsArray.size(); ++i) {
    auto &material = materialsArray[i];
    if (!material.IsObject()) {
      return false;
    };

    Str name; // materials[i].name
    if (!this->AcquireString(material, "name", &name)) {
      name = "N/A" + std::to_string(i);
    }

    GLBMaterial mat;
    if (!this->AcquireBool(material, "doubleSided",
                           &mat.doubleSided)) { // materials[i].doubleSided
      mat.doubleSided = false;
    }

    JsonNode occlusionTexture;
    if (this->AcquireObject(
            material, "occlusionTexture",
            &occlusionTexture)) { // materials[i].occlusionTexture
      if (!this->AcquireInt(
              occlusionTexture, "index",
              &mat.occlusionTexture)) { // materials[i].occlusionTexture.index
        return false;
      }
    }

    JsonNode normalMap;
    if (this->AcquireObject(material, "normalMap",
                            &normalMap)) { // materials[i].normalMap
      if (!this->AcquireInt(
              normalMap, "index",
              &mat.normalTexture)) { // materials[i].normalMap.index
        return false;
      }
    }

    if (!this->AcquireInt(
            material, "emissiveTexture",
            &mat.emissiveTexture)) { // materials[i].emissiveTexture
      mat.emissiveTexture = -1;
    }

    Vec<Float> emissiveFactor;
    if (!this->AcquireArray(material, "emissiveFactor",
                            &emissiveFactor)) { // materials[i].emissiveFactor
      mat.emissiveFactor = vec4(0, 0, 0, 0);
    } else {
      if (emissiveFactor.size() != 3) {
        return false;
      }
      mat.emissiveFactor =
          vec4(emissiveFactor[0], emissiveFactor[1], emissiveFactor[2], 1);
    }

    JsonNode pbrMetallicRoughness;
    if (this->AcquireObject(
            material, "pbrMetallicRoughness",
            &pbrMetallicRoughness)) { // materials[i].pbrMetallicRoughness
      if (!this->ParsePBRMaterial(pbrMetallicRoughness,
                                  mat.pbrMetallicRoughness)) {
        return false;
      }
    }
  }

  return true;
}

Bool GLBParser::ParseMeshes() {
  Vec<JsonNode> meshesArray;
  if (!this->AcquireArray(mJsonData, "meshes", &meshesArray)) {
    return false;
  }

  for (int i = 0; i < meshesArray.size(); ++i) {
    auto &mesh = meshesArray[i];
    GLBMesh data;
    if (!mesh.IsObject()) {
      return false;
    }

    if (!this->AcquireString(mesh, "name", &data.name)) {
      data.name = "N/A" + std::to_string(i);
    }

    Vec<JsonNode> primitivesArray;
    if (!this->AcquireArray(mesh, "primitives", &primitivesArray)) {
      return false;
    }

    for (auto &primitive : primitivesArray) {
      GLBPrimitive primData;
      if (!primitive.IsObject()) {
        return false;
      }

      JsonNode attributes;
      if (!this->AcquireObject(
              primitive, "attributes",
              &attributes)) { // meshes[i].primitives[j].attributes
        return false;
      }

      if (!attributes.IsObject()) {
        return false;
      };

      if (!this->ParseAttribute(attributes, primData.attribute)) {
        return false;
      }

      if (!this->AcquireUint(primitive, "indices", &primData.indices)) {
        return false;
      }

      if (!this->AcquireInt(primitive, "material", &primData.material)) {
        primData.material = -1;
      }

      data.primitives.push_back(primData);
    }

    mMeshes.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseTextures() {
  Vec<JsonNode> texturesArray;
  if (!this->AcquireArray(mJsonData, "textures", &texturesArray)) {
    return false;
  }

  for (auto &texture : texturesArray) {
    if (!texture.IsObject()) {
      return false;
    }

    GLBTexture data;
    if (!this->AcquireUint(texture, "sampler", &data.sampler)) {
      return false;
    }

    if (!this->AcquireUint(texture, "source", &data.source)) {
      return false;
    }

    mTextures.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseImages() {
  if (!mJsonData.Has("images")) {
    return false;
  }
  JsonNode images = mJsonData["images"]; // images

  if (!images.IsArray()) {
    return false;
  }
  Vec<JsonNode> imagesArray = images.GetArray();

  for (auto &image : imagesArray) {
    if (!image.IsObject()) {
      return false;
    }

    GLBImage data;
    if (!image.Has("name")) {
      data.name = "N/A";
    } else {
      JsonNode name = image["name"]; // images[i].name
      if (!name.IsString()) {
        return false;
      }
      data.name = name.GetString();
    }

    if (!image.Has("mimeType")) {
      return false;
    }
    JsonNode mimeType = image["mimeType"]; // images[i].mimeType
    if (!mimeType.IsString()) {
      return false;
    }
    Str type = mimeType.GetString();

    if (type == "image/jpeg") {
      data.mimeType = MimeType::JPEG;
    } else if (type == "image/png") {
      data.mimeType = MimeType::PNG;
    } else {
      return false;
    }

    if (!image.Has("bufferView")) {
      return false;
    }
    JsonNode bufferView = image["bufferView"]; // images[i].bufferView
    if (!bufferView.IsNumber()) {
      return false;
    }
    data.bufferView = static_cast<Uint>(bufferView.GetNumber());

    mImages.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseSkins() {
  if (!mJsonData.Has("skins")) {
    return false;
  }
  JsonNode skins = mJsonData["skins"]; // skins

  if (!skins.IsArray()) {
    return false;
  }
  Vec<JsonNode> skinsArray = skins.GetArray();

  for (auto &skin : skinsArray) {
    if (!skin.IsObject()) {
      return false;
    }

    GLBSkin data;
    if (!skin.Has("inverseBindMatrices")) {
      return false;
    }
    JsonNode inverseBindMatrices =
        skin["inverseBindMatrices"]; // skins[i].inverseBindMatrices
    if (!inverseBindMatrices.IsNumber()) {
      return false;
    }
    data.inverseBindMatrices =
        static_cast<Uint>(inverseBindMatrices.GetNumber());

    if (!skin.Has("joints")) {
      return false;
    }
    JsonNode joints = skin["joints"]; // skins[i].joints
    if (!joints.IsArray()) {
      return false;
    }
    Vec<JsonNode> jointsArray = joints.GetArray();

    for (auto &joint : jointsArray) {
      if (!joint.IsNumber()) {
        return false;
      }
      Uint jointIndex = static_cast<Uint>(joint.GetNumber());
      data.joints.push_back(jointIndex);
    }

    mSkins.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseAccessors() {
  Vec<JsonNode> accessorsArray;
  if (!this->AcquireArray(mJsonData, "accessors", &accessorsArray)) {
    return false;
  }

  for (auto &accessor : accessorsArray) {
    GLBAccessor data;
    if (!accessor.IsObject()) {
      return false;
    }

    if (!this->AcquireUint(accessor, "bufferView",
                           &data.bufferView)) { // accessors[i].bufferView
      return false;
    }

    if (!this->AcquireUint(accessor, "componentType",
                           &data.componentType)) { // accessors[i].componentType
      return false;
    }

    if (!this->AcquireUint(accessor, "count",
                           &data.count)) { // accessors[i].count
      return false;
    }

    if (!this->AcquireString(accessor, "type",
                             &data.type)) { // accessors[i].type
      return false;
    }

    if (!this->AcquireArray(accessor, "min", &data.min)) { // accessors[i].min
      data.min = Vec<Float>({0, 0, 0});
    }

    if (!this->AcquireArray(accessor, "max", &data.max)) { // accessors[i].max
      data.max = Vec<Float>({0, 0, 0});
    }

    mAccessors.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseBufferViews() {
  Vec<JsonNode> bufferViewsArray;
  if (!this->AcquireArray(mJsonData, "bufferViews", &bufferViewsArray)) {
    return false;
  }

  for (auto &bufferView : bufferViewsArray) {
    GLBBufferView data;
    if (!bufferView.IsObject()) {
      return false;
    }

    if (!this->AcquireUint(bufferView, "buffer",
                           &data.buffer)) { // bufferViews[i].buffer
      return false;
    }

    if (!this->AcquireUint(bufferView, "byteLength",
                           &data.byteLength)) { // bufferViews[i].byteLength
      return false;
    }

    if (!this->AcquireUint(bufferView, "byteOffset",
                           &data.byteOffset)) { // bufferViews[i].byteOffset
      return false;
    }

    if (!this->AcquireInt(bufferView, "target",
                          &data.target)) { // bufferViews[i].target
      data.target = -1;
    }

    mBufferViews.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseSamplers() {
  Vec<JsonNode> samplersArray;
  if (!this->AcquireArray(mJsonData, "samplers", &samplersArray)) {
    return false;
  }

  for (auto &sampler : samplersArray) {
    GLBSampler data;
    if (!sampler.IsObject()) {
      return false;
    }

    if (!this->AcquireUint(sampler, "magFilter",
                           &data.magFilter)) { // samplers[i].magFilter
      return false;
    }

    if (!this->AcquireUint(sampler, "minFilter",
                           &data.minFilter)) { // samplers[i].minFilter
      return false;
    }

    if (!this->AcquireUint(sampler, "wrapS",
                           &data.wrapS)) { // samplers[i].wrapS
      data.wrapS = (Uint)WrappingType::REPEAT;
    }

    if (!this->AcquireUint(sampler, "wrapT",
                           &data.wrapT)) { // samplers[i].wrapT
      data.wrapT = (Uint)WrappingType::REPEAT;
    }

    mSamplers.push_back(data);
  }

  return true;
}

Bool GLBParser::ParseBuffers() {
  Vec<JsonNode> buffersArray;
  if (!this->AcquireArray(mJsonData, "buffers", &buffersArray)) {
    return false;
  }

  for (auto &buffer : buffersArray) {
    GLBBuffer data;
    if (!buffer.IsObject()) {
      return false;
    }

    if (!this->AcquireUint(buffer, "byteLength",
                           &data.byteLength)) { // buffers[i].byteLength
      return false;
    }

    mBuffers.push_back(data);
  }

  return true;
}

Bool GLBParser::Parse() {
  if (!this->ParseHeader()) {
    return false;
  }
  if (!this->ParseAsset()) {
    return false;
  }
  if (!this->ParseScene()) {
    return false;
  }
  if (!this->ParseNodes()) {
    return false;
  }
  if (!this->ParseMaterials()) {
    return false;
  }
  if (!this->ParseMeshes()) {
    return false;
  }
  if (!this->ParseTextures()) {
    return false;
  }
  if (!this->ParseImages()) {
    return false;
  }
  if (!this->ParseSkins()) {
    return false;
  }
  if (!this->ParseAccessors()) {
    return false;
  }
  if (!this->ParseBufferViews()) {
    return false;
  }
  if (!this->ParseSamplers()) {
    return false;
  }
  if (!this->ParseBuffers()) {
    return false;
  }
  return true;
}
} // namespace Parser
} // namespace GeoFrame
