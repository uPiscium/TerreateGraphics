#include "../includes/loader.hpp"
#include <fstream>
#include <iomanip>

namespace GeoFrame {
namespace Parser {
ObjectID const Serializer::sOID = ObjectID("SELIALIZER");
ObjectID const ParserBase::sOID = ObjectID("PARSER_BASE");
ObjectID const JsonParser::sOID = ObjectID("JSON_PARSER");

Byte IOBuffer::GetChar() {
  if (mCursor == mEnd) {
    return -1;
  }
  if (*mCursor == '\n') {
    ++mLine;
  }
  Byte const chr = *mCursor & 0xff;
  ++mCursor;
  return chr;
}

Str IOBuffer::GetWord() {
  if (mCursor == mEnd) {
    return "";
  }

  Stream buffer;
  this->SkipWhiteSpace();
  while (!(*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
           *mCursor == '\r')) {
    buffer << *mCursor;
    ++mCursor;

    if (mCursor == mEnd) {
      break;
    }
  }
  return buffer.str();
}

Byte IOBuffer::FetchChar() {
  if (mCursor == mEnd) {
    return -1;
  }
  Byte const chr = *mCursor; // & 0xff;
  return chr;
}

Str IOBuffer::FetchWord() {
  if (mCursor == mEnd) {
    return "";
  }

  Stream buffer;
  this->SkipWhiteSpace();
  Iter cursor = mCursor;
  while (!(*cursor == ' ' || *cursor == '\t' || *cursor == '\n' ||
           *cursor == '\r')) {
    buffer << *cursor;
    ++cursor;

    if (cursor == mEnd) {
      break;
    }
  }
  return buffer.str();
}

void IOBuffer::UngetChar() {
  --mCursor;
  if (*mCursor == '\n') {
    --mLine;
  }
}

void IOBuffer::UngetWord() {
  while (mCursor != mBegin) {
    if (*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
        *mCursor == '\r') {
      if (*mCursor == '\n') {
        --mLine;
      }
      --mCursor;
    } else {
      break;
    }
  }
  while (mCursor != mBegin) {
    if (!(*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
          *mCursor == '\r')) {
      --mCursor;
    } else {
      break;
    }
  }
}

void IOBuffer::SkipWhiteSpace() {
  while (mCursor != mEnd) {
    if (*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
        *mCursor == '\r') {
      if (*mCursor == '\n') {
        ++mLine;
      }
      ++mCursor;
    } else {
      break;
    }
  }
}

Size IOBuffer::Find(Byte const &chr) {
  Iter cursor = mCursor;
  while (cursor != mEnd) {
    if (*cursor == chr) {
      return (Size)(cursor - mCursor);
    }
    ++cursor;
  }
  return -1;
}

Size IOBuffer::Find(Str const &pattern) {
  Iter cursor = mCursor;
  while (cursor != mEnd) {
    if (std::equal(pattern.begin(), pattern.end(), cursor)) {
      return (Size)(cursor - mCursor);
    }
    ++cursor;
  }
  return -1;
}

Bool IOBuffer::Match(Byte const &chr) {
  if (mCursor == mEnd) {
    return false;
  }
  if (*mCursor == chr) {
    return true;
  }
  return false;
}

Bool IOBuffer::Match(Str const &pattern) {
  if (mCursor == mEnd) {
    return false;
  }
  if (std::equal(pattern.begin(), pattern.end(), mCursor)) {
    return true;
  }
  return false;
}

Bool IOBuffer::Except(Byte const &chr) {
  if (mCursor == mEnd) {
    return false;
  }
  if (*mCursor != chr) {
    ++mCursor;
    return true;
  }
  return false;
}

Bool IOBuffer::Except(Str const &pattern) {
  if (mCursor == mEnd) {
    return false;
  }
  if (!std::equal(pattern.begin(), pattern.end(), mCursor)) {
    mCursor += pattern.size();
    return true;
  }
  return false;
}

void IOBuffer::Read(Byte *buffer, Size const &size) {
  if (mCursor + size > mEnd) {
    M_GEO_THROW(InterfaceError, "End of buffer");
  }
  std::copy(mCursor, mCursor + size, buffer);
  mCursor += size;
}

void IOBuffer::Unread(Size const &size) {
  if (mCursor - size < mBegin) {
    M_GEO_THROW(InterfaceError, "Begin of buffer");
  }
  mCursor -= size;
}

void IOBuffer::Ignore(Size const &size) {
  if (mCursor + size > mEnd) {
    M_GEO_THROW(InterfaceError, "End of buffer");
  }
  mCursor += size;
}

IOBuffer &IOBuffer::operator++() {
  if (mCursor == mEnd) {
    M_GEO_THROW(InterfaceError, "End of buffer");
  }
  if (*mCursor == '\n') {
    ++mLine;
  }
  ++mCursor;
  return *this;
}

IOBuffer &IOBuffer::operator--() {
  if (mCursor == mBegin) {
    M_GEO_THROW(InterfaceError, "Begin of buffer");
  }
  --mCursor;
  if (*mCursor == '\n') {
    --mLine;
  }
  return *this;
}

IOBuffer &IOBuffer::operator+=(Uint const &size) {
  if (mCursor + size > mEnd) {
    M_GEO_THROW(InterfaceError, "End of buffer");
  }
  mCursor += size;
  return *this;
}

IOBuffer &IOBuffer::operator-=(Uint const &size) {
  if (mCursor - size < mBegin) {
    M_GEO_THROW(InterfaceError, "Begin of buffer");
  }
  mCursor -= size;
  return *this;
}

void Node::Erase() {
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

Node::Node(DataType const &type) : mType(type) {
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

Node::Node(Node const &other) : mType(other.mType) {
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

Bool Node::GetBool() const {
  if (mType != DataType::BOOL_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mBool;
}

Double Node::GetNumber() const {
  if (mType != DataType::NUMBER_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mNumber;
}

Str const &Node::GetString() const {
  if (mType != DataType::STRING_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mString;
}

Node::Array const &Node::GetArray() const {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mArray;
}

Node::Object const &Node::GetObject() const {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return *mStorage.mObject;
}

void Node::SetBool(Bool const &value) {
  this->Erase();
  mType = DataType::BOOL_TYPE;
  mStorage.mBool = value;
}

void Node::SetNumber(Double const &value) {
  this->Erase();
  mType = DataType::NUMBER_TYPE;
  mStorage.mNumber = value;
}

void Node::SetString(Str const &value) {
  this->Erase();
  mType = DataType::STRING_TYPE;
  mStorage.mString = new Str(value);
}

void Node::SetArray(Array const &value) {
  this->Erase();
  mType = DataType::ARRAY_TYPE;
  mStorage.mArray = new Array(value);
}

void Node::SetObject(Object const &value) {
  this->Erase();
  mType = DataType::OBJECT_TYPE;
  mStorage.mObject = new Object(value);
}

Bool Node::Has(Str const &key) const {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return mStorage.mObject->find(key) != mStorage.mObject->end();
}

Bool Node::Has(Size const &index) const {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  return index <= mStorage.mArray->size();
}

Bool Node::EvalAsBool() const {
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

Str Node::ToString() const {
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

Node &Node::operator=(Bool const &value) {
  this->SetBool(value);
  return *this;
}

Node &Node::operator=(Double const &value) {
  this->SetNumber(value);
  return *this;
}

Node &Node::operator=(Str const &value) {
  this->SetString(value);
  return *this;
}

Node &Node::operator=(Array const &value) {
  this->SetArray(value);
  return *this;
}

Node &Node::operator=(Object const &value) {
  this->SetObject(value);
  return *this;
}

Node &Node::operator=(Node const &other) {
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

Node &Node::operator[](Size const &index) {
  if (mType != DataType::ARRAY_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  if (this->Has(index)) {
    return mStorage.mArray->at(index);
  } else {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
}

Node &Node::operator[](Str const &key) {
  if (mType != DataType::OBJECT_TYPE) {
    M_GEO_THROW(InterfaceError, "Type mismatch");
  }
  if (this->Has(key)) {
    return mStorage.mObject->at(key);
  } else {
    M_GEO_THROW(InterfaceError, "Key not found");
  }
}

Str Serializer::Indent(Size const &level) {
  Stream buffer;
  buffer << (mIndent == 0 ? "" : "\n");
  for (Size i = 0; i < level * mIndent; ++i) {
    buffer << ' ';
  }
  return buffer.str();
}

Str Serializer::Escape(Byte const &chr) {
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

Str Serializer::ConvertToUnicode(Byte const &chr) {
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

Str Serializer::Serialize(Node const &node, Size const &level) {
  Node::DataType const type = node.GetType();
  Stream buffer;
  switch (type) {
  case Node::DataType::STRING_TYPE:
    buffer << '"';
    for (auto const &chr : node.GetString()) {
      buffer << this->Escape(chr);
    }
    buffer << '"';
    break;
  case Node::DataType::ARRAY_TYPE:
    buffer << '[';
    for (Node::Array::const_iterator begin = node.GetArray().begin(),
                                     end = node.GetArray().end();
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
  case Node::DataType::OBJECT_TYPE:
    buffer << '{';
    for (Node::Object::const_iterator begin = node.GetObject().begin(),
                                      end = node.GetObject().end();
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
    buffer << node.ToString();
    break;
  }
  return buffer.str();
}

ParserBase::ParserBase(Str const &filename) : Geobject(ParserBase::sOID) {
  std::ifstream file;
  file.open(filename, std::ios::in);
  if (!file.is_open()) {
    M_GEO_THROW(InterfaceError, "Failed to open file");
  }

  Stream buffer;
  buffer << file.rdbuf();
  file.close();

  mFiledata = buffer.str();
  mBuffer = std::make_shared<IOBuffer>(mFiledata.begin(), mFiledata.end());
}

ParserBase::ParserBase(ObjectID const &oid, Str const &filename)
    : Geobject(oid) {
  std::ifstream file;
  file.open(filename, std::ios::in);
  if (!file.is_open()) {
    M_GEO_THROW(InterfaceError, "Failed to open file");
  }

  Stream buffer;
  buffer << file.rdbuf();
  file.close();

  mFiledata = buffer.str();
  mBuffer = std::make_shared<IOBuffer>(mFiledata.begin(), mFiledata.end());
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

Bool JsonParser::ParseNull(Node &node) {
  if (mBuffer->Match("null")) {
    mBuffer->Ignore(4); // Skip "null"
    node = Node();
    return true;
  }
  return false;
}

Bool JsonParser::ParseBool(Node &node) {
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

Bool JsonParser::ParseNumber(Node &node) {
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

Bool JsonParser::ParseString(Node &node) {
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

Bool JsonParser::ParseArray(Node &node) {
  if (!mBuffer->Match('[')) {
    return false;
  }
  mBuffer->Ignore(1); // Skip '['

  Node::Array array;
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

Bool JsonParser::ParseObject(Node &node) {
  if (!mBuffer->Match('{')) {
    return false;
  }
  mBuffer->Ignore(1); // Skip '{'

  Node::Object object;
  while (1) {
    mBuffer->SkipWhiteSpace();
    Node key(Node::DataType::STRING_TYPE);
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

namespace Loader {
ObjectID const Material::sOID = ObjectID("MATERIAL");
ObjectID const LoaderBase::sOID = ObjectID("LOADER_BASE");

Shared<Core::Texture> const &
Material::GetTexture(MaterialTexture const &type) const {
  if (mTextures.find(type) == mTextures.end()) {
    M_GEO_THROW(InterfaceError, "Texture not found");
  }
  return mTextures.at(type);
}

vec3 const &Material::GetColor(MaterialColor const &type) const {
  if (mColors.find(type) == mColors.end()) {
    M_GEO_THROW(InterfaceError, "Color not found");
  }
  return mColors.at(type);
}

Float const &Material::GetConstant(MaterialConstant const &type) const {
  if (mConstants.find(type) == mConstants.end()) {
    M_GEO_THROW(InterfaceError, "Constant not found");
  }
  return mConstants.at(type);
}
} // namespace Loader
} // namespace GeoFrame
