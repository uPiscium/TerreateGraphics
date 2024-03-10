#include "../../includes/parser/glb.hpp"

namespace GeoFrame {
namespace Parser {
ObjectID const GLBParser::sOID = ObjectID("GLB_PARSER");

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
  JsonNode node = parser.GetNode();
  return true;
}

Bool GLBParser::ParseJson() { return true; }

Bool GLBParser::ParseBinary() { return true; }

Bool GLBParser::Parse() {
  if (!this->ParseHeader()) {
    return false;
  }
  if (!this->ParseJson()) {
    return false;
  }
  if (!this->ParseBinary()) {
    return false;
  }
  return true;
}
} // namespace Parser
} // namespace GeoFrame
