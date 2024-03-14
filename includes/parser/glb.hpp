#pragma once
#include "../context.hpp"
#include "json.hpp"

namespace GeoFrame {
namespace Parser {
class GLBParser : public ParserBase {
protected:
  enum class MimeType { JPEG, PNG, UNKNOWN };

  struct GLBScene {
    Str name;
    Vec<Uint> nodes;
  };

  struct GLBNode {
    Str name;
    Uint mesh;
    Uint skin;
    Vec<Uint> children;
    vec3 scale;
    Quaternion rotation;
    vec3 translation;
  };

  struct PBRMetallicRoughness {
    vec4 baseColorFactor;
    Float metallicFactor;
    Float roughnessFactor;
    Uint baseColorTexture;
  };

  struct GLBMaterial {
    Str name;
    Bool doubleSided;
    Int occlusionTexture;
    Int normalTexture;
    vec4 emissiveFactor;
    Int emissiveTexture;
    Vec<Str> extensions;
    PBRMetallicRoughness pbrMetallicRoughness;
  };

  struct GLBAttribute {
    Uint position;
    Int normal;
    Vec<Uint> texCoord;
    Vec<vec4> color;
    Vec<Uint> joint;
    Vec<Uint> weight;
  };

  struct GLBPrimitive {
    GLBAttribute attribute;
    Uint indices;
    Int material;
  };

  struct GLBMesh {
    Str name;
    Vec<GLBPrimitive> primitives;
  };

  struct GLBTexture {
    Uint sampler;
    Uint source;
  };

  struct GLBImage {
    Str name;
    MimeType mimeType;
    Uint bufferView;
  };

  struct GLBSampler {
    Uint magFilter;
    Uint minFilter;
    Uint wrapS;
    Uint wrapT;
  };

  struct GLBSkin {
    Uint inverseBindMatrices;
    Vec<Uint> joints;
  };

  struct GLBBufferView {
    Uint buffer;
    Uint byteLength;
    Uint byteOffset;
    Int target;
  };

  struct GLBAccessor {
    Uint bufferView;
    Uint componentType;
    Uint count;
    Str type;
    Vec<Float> min;
    Vec<Float> max;
  };

  struct GLBBuffer {
    Uint byteLength;
  };

private:
  Context::Context mContext;
  Vec<GLBScene> mScenes;
  Vec<GLBNode> mNodes;
  Vec<GLBMaterial> mMaterials;
  Vec<GLBMesh> mMeshes;
  Vec<GLBTexture> mTextures;
  Vec<GLBImage> mImages;
  Vec<GLBSampler> mSamplers;
  Vec<GLBSkin> mSkins;
  Vec<GLBBufferView> mBufferViews;
  Vec<GLBAccessor> mAccessors;
  Vec<GLBBuffer> mBuffers;
  JsonNode mJsonData;

  Str mVersion;
  Str mGenerator;
  Vec<Str> mExtensions;

protected:
  Bool ParsePBRMaterial(JsonNode &node, PBRMetallicRoughness &material);
  Bool ParseAttribute(JsonNode &node, GLBAttribute &attr);
  Bool AcquireBool(JsonNode &node, Str const &key, Bool *value);
  Bool AcquireNumber(JsonNode &node, Str const &key, Float *value);
  Bool AcquireInt(JsonNode &node, Str const &key, Int *value);
  Bool AcquireUint(JsonNode &node, Str const &key, Uint *value);
  Bool AcquireString(JsonNode &node, Str const &key, Str *value);
  Bool AcquireArray(JsonNode &node, Str const &key, Vec<Bool> *array);
  Bool AcquireArray(JsonNode &node, Str const &key, Vec<Float> *array);
  Bool AcquireArray(JsonNode &node, Str const &key, Vec<Uint> *array);
  Bool AcquireArray(JsonNode &node, Str const &key, Vec<Str> *array);
  Bool AcquireArray(JsonNode &node, Str const &key, Vec<JsonNode> *array);
  Bool AcquireObject(JsonNode &node, Str const &key, JsonNode *object);

public:
  static ObjectID const sOID;

public:
  GLBParser(Str const &filename) : ParserBase(GLBParser::sOID, filename) {}
  GLBParser(Shared<IOBuffer> buffer);
  ~GLBParser() override {}

  Bool ParseHeader();
  Bool ParseAsset();
  Bool ParseScene();
  Bool ParseNodes();
  Bool ParseMaterials();
  Bool ParseMeshes();
  Bool ParseTextures();
  Bool ParseImages();
  Bool ParseSkins();
  Bool ParseAccessors();
  Bool ParseBufferViews();
  Bool ParseSamplers();
  Bool ParseBuffers();
  Bool Parse();
};
} // namespace Parser
} // namespace GeoFrame
