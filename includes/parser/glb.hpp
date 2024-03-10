#pragma once
#include "json.hpp"

namespace GeoFrame {
namespace Parser {
class GLBParser : public ParserBase {
private:
  Vec<vec3> mVertices;
  Vec<vec3> mNormals;
  Vec<vec2> mUVs;
  Vec<Vec<Uint>> mMatrixIndices;
  Vec<Uint> mIndices;

public:
  static ObjectID const sOID;

public:
  GLBParser(Str const &filename) : ParserBase(GLBParser::sOID, filename) {}
  GLBParser(Shared<IOBuffer> buffer);
  ~GLBParser() override {}

  Bool ParseHeader();
  Bool ParseJson();
  Bool ParseBinary();
  Bool Parse();
};
} // namespace Parser
} // namespace GeoFrame
