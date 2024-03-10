#include "../../includes/parser/json.hpp"

namespace GeoFrame {
namespace Parser {
ObjectID const JsonSerializer::sOID = ObjectID("JSON_SELIALIZER");
ObjectID const JsonParser::sOID = ObjectID("JSON_PARSER");

void JsonNode::Erase() {
  switch (mType) {
  case DataType::STRING_TYPE:
    delete mStorage.mString;
    break;
  case DataType::ARRAY_TYPE:
    delete mStorage.mArray;
    break;
  case DataType::OBJECT_TYPE:
    delete mStorage.mObject;
    break;
  default:
    break;
  }
}

JsonNode::JsonNode(DataType const &type) : mType(type) {
  switch (mType) {
  case DataType::BOOL_TYPE:
    mStorage.mBool = false;
    break;
  case DataType::NUMBER_TYPE:
    mStorage.mNumber = 0.0f;
    break;
  case DataType::STRING_TYPE:
    mStorage.mString = new Str();
    break;
  case DataType::ARRAY_TYPE:
    mStorage.mArray = new Array();
    break;
  case DataType::OBJECT_TYPE:
    mStorage.mObject = new Object();
    break;
  default:
    break;
  }
}

JsonNode::JsonNode(JsonNode const &other) : mType(other.mType) {
  switch (mType) {
  case DataType::BOOL_TYPE:
    mStorage.mBool = other.mStorage.mBool;
    break;
  case DataType::NUMBER_TYPE:
    mStorage.mNumber = other.mStorage.mNumber;
    break;
  case DataType::STRING_TYPE:
    mStorage.mString = new Str(*other.mStorage.mString);
    break;
  case DataType::ARRAY_TYPE:
    mStorage.mArray = new Array(*other.mStorage.mArray);
    break;
  case DataType::OBJECT_TYPE:
    mStorage.mObject = new Object(*other.mStorage.mObject);
    break;
  default:
    break;
  }
}

Bool JsonNode::GetBool() const {
  if (mType != DataType::BOOL_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mBool;
}

Double JsonNode::GetNumber() const {
  if (mType != DataType::NUMBER_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mNumber;
}

Str const &JsonNode::GetString() const {
  if (mType != DataType::STRING_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mString;
}

JsonNode::Array const &JsonNode::GetArray() const {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mArray;
}

JsonNode::Object const &JsonNode::GetObject() const {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mObject;
}

void JsonNode::SetBool(Bool const &value) {
  this->Erase();
  mType = DataType::BOOL_TYPE;
  mStorage.mBool = value;
}

void JsonNode::SetNumber(Double const &value) {
  this->Erase();
  mType = DataType::NUMBER_TYPE;
  mStorage.mNumber = value;
}

void JsonNode::SetString(Str const &value) {
  this->Erase();
  mType = DataType::STRING_TYPE;
  mStorage.mString = new Str(value);
}

void JsonNode::SetArray(Array const &value) {
  this->Erase();
  mType = DataType::ARRAY_TYPE;
  mStorage.mArray = new Array(value);
}

void JsonNode::SetObject(Object const &value) {
  this->Erase();
  mType = DataType::OBJECT_TYPE;
  mStorage.mObject = new Object(value);
}

Bool JsonNode::Has(Str const &key) const {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mObject->find(key) != mStorage.mObject->end();
}

Bool JsonNode::Has(Size const &index) const {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return index <= mStorage.mArray->size();
}

Bool JsonNode::EvalAsBool() const {
  switch (mType) {
  case DataType::BOOL_TYPE:
    return mStorage.mBool;
  case DataType::NUMBER_TYPE:
    return mStorage.mNumber != 0.0f;
  case DataType::STRING_TYPE:
    return !mStorage.mString->empty();
  case DataType::ARRAY_TYPE:
    return !mStorage.mArray->empty();
  case DataType::OBJECT_TYPE:
    return !mStorage.mObject->empty();
  default:
    return false;
  }
}

Str JsonNode::ToString() const {
  switch (mType) {
  case DataType::BOOL_TYPE:
    return mStorage.mBool ? "true" : "false";
  case DataType::NUMBER_TYPE:
    return std::to_string(mStorage.mNumber);
  case DataType::STRING_TYPE:
    return *mStorage.mString;
  case DataType::ARRAY_TYPE:
    return "Array";
  case DataType::OBJECT_TYPE:
    return "Object";
  default:
    return "null";
  }
}

JsonNode &JsonNode::operator=(Bool const &value) {
  this->SetBool(value);
  return *this;
}

JsonNode &JsonNode::operator=(Double const &value) {
  this->SetNumber(value);
  return *this;
}

JsonNode &JsonNode::operator=(Str const &value) {
  this->SetString(value);
  return *this;
}

JsonNode &JsonNode::operator=(Array const &value) {
  this->SetArray(value);
  return *this;
}

JsonNode &JsonNode::operator=(Object const &value) {
  this->SetObject(value);
  return *this;
}

JsonNode &JsonNode::operator=(JsonNode const &other) {
  if (this != &other) {
    this->Erase();
    mType = other.mType;
    switch (mType) {
    case DataType::BOOL_TYPE:
      mStorage.mBool = other.mStorage.mBool;
      break;
    case DataType::NUMBER_TYPE:
      mStorage.mNumber = other.mStorage.mNumber;
      break;
    case DataType::STRING_TYPE:
      mStorage.mString = new Str(*other.mStorage.mString);
      break;
    case DataType::ARRAY_TYPE:
      mStorage.mArray = new Array(*other.mStorage.mArray);
      break;
    case DataType::OBJECT_TYPE:
      mStorage.mObject = new Object(*other.mStorage.mObject);
      break;
    default:
      break;
    }
  }
  return *this;
}

JsonNode &JsonNode::operator[](Size const &index) {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  if (this->Has(index)) {
    return mStorage.mArray->at(index);
  } else {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
}

JsonNode &JsonNode::operator[](Str const &key) {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  if (this->Has(key)) {
    return mStorage.mObject->at(key);
  } else {
    M_GEO_THROW(InterfaceError, "Key not found");
  }
}

Str JsonSerializer::Indent(Size const &level) {
  Stream buffer;
  buffer << (mIndent == 0 ? "" : "\n");
  for (Size i = 0; i < level * mIndent; ++i) {
    buffer << ' ';
  }
  return buffer.str();
}

Str JsonSerializer::Escape(Byte const &chr) {
  switch (chr) {
  case '"':
    return "\\\"";
  case '\\':
    return "\\\\";
  case '\b':
    return "\\b";
  case '\f':
    return "\\f";
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\t':
    return "\\t";
  default:
    Str buf;
    buf += chr;
    return buf;
  }
}

Str JsonSerializer::ConvertToUnicode(Byte const &chr) {
  Stream buffer;
  if (chr < 0x20 || chr > 0x7E) {
    Byte const hex = chr & 0xFF;
    buffer << "\\u";
    buffer << std::setfill('0') << std::setw(4) << hex;
    buffer << 'x';
    return buffer.str();
  }
  buffer << chr;
  return buffer.str();
}

Str JsonSerializer::Serialize(JsonNode const &JsonNode, Size const &level) {
  JsonNode::DataType const type = JsonNode.GetType();
  Stream buffer;
  switch (type) {
  case JsonNode::DataType::STRING_TYPE:
    buffer << '"';
    for (auto const &chr : JsonNode.GetString()) {
      buffer << this->Escape(chr);
    }
    buffer << '"';
    break;
  case JsonNode::DataType::ARRAY_TYPE:
    buffer << '[';
    for (JsonNode::Array::const_iterator begin = JsonNode.GetArray().begin(),
                                         end = JsonNode.GetArray().end();
         begin != end; ++begin) {
      buffer << this->Indent(level + 1);
      buffer << this->Serialize(*begin, level + 1);
      if (std::next(begin) != end) {
        buffer << ", ";
      }
    }
    buffer << this->Indent(level);
    buffer << "]";
    break;
  case JsonNode::DataType::OBJECT_TYPE:
    buffer << '{';
    for (JsonNode::Object::const_iterator begin = JsonNode.GetObject().begin(),
                                          end = JsonNode.GetObject().end();
         begin != end; ++begin) {
      buffer << this->Indent(level + 1);
      buffer << '"';
      for (auto const &chr : begin->first) {
        buffer << this->Escape(chr);
      }
      buffer << '"';
      buffer << ": ";
      buffer << this->Serialize(begin->second, level + 1);
      if (std::next(begin) != end) {
        buffer << ", ";
      }
    }
    buffer << this->Indent(level);
    buffer << '}';
    break;
  default:
    buffer << JsonNode.ToString();
    break;
  }
  return buffer.str();
}

JsonParser::JsonParser(Str const &filename, Size const &maxDepth)
    : ParserBase(JsonParser::sOID, filename), mDepth(maxDepth) {
  if (mDepth <= 0) {
    M_GEO_THROW(InterfaceError, "Invalid depth");
  }
}

JsonParser::JsonParser(Shared<IOBuffer> buffer, Size const &depth)
    : ParserBase(JsonParser::sOID, buffer), mDepth(depth) {
  if (mDepth <= 0) {
    M_GEO_THROW(InterfaceError, "Maximum depth exceeded");
  }
}

Bool JsonParser::ParseNull(JsonNode &node) {
  if (mBuffer->Match("null")) {
    mBuffer->Ignore(4); // Skip "null"
    node = JsonNode();
    return true;
  }
  return false;
}

Bool JsonParser::ParseBool(JsonNode &node) {
  if (mBuffer->Match("true")) {
    mBuffer->Ignore(4); // Skip "true"
    node = true;
    return true;
  }
  if (mBuffer->Match("false")) {
    mBuffer->Ignore(5); // Skip "false"
    node = false;
    return true;
  }
  return false;
}

Bool JsonParser::ParseNumber(JsonNode &node) {
  Stream buffer;
  while (1) {
    Byte chr = mBuffer->GetChar();
    if (chr == -1) {
      return false;
    }

    if (('0' <= chr && chr <= '9') || chr == '+' || chr == '-' || chr == '.' ||
        chr == 'e' || chr == 'E') {
      buffer << chr;
      continue;
    }
    mBuffer->UngetChar();
    node = std::stod(buffer.str());
    return true;
  }
}

Bool JsonParser::ParseString(JsonNode &node) {
  if (!mBuffer->Match('"')) {
    return false;
  }
  mBuffer->Ignore(1); // Skip '"'

  Stream rstBuffer;
  while (1) {
    Byte chr = mBuffer->GetChar();
    switch (chr) {
    case -1:
      return false;
    case '"':
      node = rstBuffer.str();
      return true;
    case '\\':
      chr = mBuffer->GetChar();
      switch (chr) {
      case -1:
        mBuffer->UngetChar();
        return false;
      case '"':
        rstBuffer << '\"';
        break;
      case '\\':
        rstBuffer << '\\';
        break;
      case '/':
        rstBuffer << '/';
        break;
      case 'b':
        rstBuffer << '\b';
        break;
      case 'f':
        rstBuffer << '\f';
        break;
      case 'n':
        rstBuffer << '\n';
        break;
      case 'r':
        rstBuffer << '\r';
        break;
      case 't':
        rstBuffer << '\t';
        break;
      default:
        rstBuffer << chr;
      }
      break;
    default:
      rstBuffer << chr;
      break;
    }
  }
}

Bool JsonParser::ParseArray(JsonNode &node) {
  if (!mBuffer->Match('[')) {
    return false;
  }
  mBuffer->Ignore(1); // Skip '['

  JsonNode::Array array;
  while (1) {
    mBuffer->SkipWhiteSpace();
    JsonParser parser(mBuffer, mDepth - 1);
    if (!parser.Parse()) {
      return false;
    }
    array.push_back(parser.GetNode());
    mBuffer->SkipWhiteSpace();

    if (mBuffer->Match(',')) {
      mBuffer->Ignore(1); // Skip ','
      continue;
    }
    if (mBuffer->Match(']')) {
      node = array;
      mBuffer->Ignore(1); // Skip ']'
      return true;
    }
    return false;
  }
}

Bool JsonParser::ParseObject(JsonNode &node) {
  if (!mBuffer->Match('{')) {
    return false;
  }
  mBuffer->Ignore(1); // Skip '{'

  JsonNode::Object object;
  while (1) {
    mBuffer->SkipWhiteSpace();
    JsonNode key(JsonNode::DataType::STRING_TYPE);
    if (!this->ParseString(key)) {
      return false;
    }
    mBuffer->SkipWhiteSpace();

    if (!mBuffer->Match(':')) {
      return false;
    }
    mBuffer->Ignore(1); // Skip ':'
    mBuffer->SkipWhiteSpace();

    JsonParser parser(mBuffer, mDepth - 1);
    if (!parser.Parse()) {
      return false;
    }
    object.insert(std::make_pair(key.GetString(), parser.GetNode()));
    mBuffer->SkipWhiteSpace();

    if (mBuffer->Match(',')) {
      mBuffer->Ignore(1); // Skip ','
      continue;
    }
    if (mBuffer->Match('}')) {
      node = object;
      mBuffer->Ignore(1); // Skip '}'
      return true;
    }

    return false;
  }
}

Bool JsonParser::Parse() {
  mBuffer->SkipWhiteSpace();
  Byte chr = mBuffer->FetchChar();
  if (chr == -1) {
    return false;
  }

  switch (chr) {
  case 'n':
    return this->ParseNull(mNode);
  case 't':
  case 'f':
    return this->ParseBool(mNode);
  case '"':
    return this->ParseString(mNode);
  case '[':
    return this->ParseArray(mNode);
  case '{':
    return this->ParseObject(mNode);
  default:
    if (('0' <= chr && chr <= '9') || chr == '+' || chr == '-') {
      return this->ParseNumber(mNode);
    }
    return false;
  }
}
} // namespace Parser
} // namespace GeoFrame
