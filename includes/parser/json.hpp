#pragma once
#include "base.hpp"

namespace GeoFrame {
namespace Parser {
class JsonNode {
public:
  using Array = Vec<JsonNode>;
  using Object = Map<Str, JsonNode>;

public:
  enum class DataType {
    NULL_TYPE,
    BOOL_TYPE,
    NUMBER_TYPE,
    STRING_TYPE,
    ARRAY_TYPE,
    OBJECT_TYPE
  };

protected:
  union Storage {
    Bool mBool;
    Double mNumber;
    Str *mString;
    Array *mArray;
    Object *mObject;
  };

protected:
  Storage mStorage;
  DataType mType;

private:
  void Erase();

public:
  JsonNode() : mType(DataType::NULL_TYPE) {}
  explicit JsonNode(Bool const &value) : mType(DataType::BOOL_TYPE) {
    mStorage.mBool = value;
  }
  explicit JsonNode(Double const &value) : mType(DataType::NUMBER_TYPE) {
    mStorage.mNumber = value;
  }
  explicit JsonNode(Str const &value) : mType(DataType::STRING_TYPE) {
    mStorage.mString = new Str(value);
  }
  explicit JsonNode(Array const &value) : mType(DataType::ARRAY_TYPE) {
    mStorage.mArray = new Array(value);
  }
  explicit JsonNode(Object const &value) : mType(DataType::OBJECT_TYPE) {
    mStorage.mObject = new Object(value);
  }
  explicit JsonNode(char const *value) : mType(DataType::STRING_TYPE) {
    mStorage.mString = new Str(value);
  }
  explicit JsonNode(DataType const &type);
  JsonNode(JsonNode const &other);
  ~JsonNode() { this->Erase(); }

  DataType const &GetType() const { return mType; }
  Bool GetBool() const;
  Double GetNumber() const;
  Str const &GetString() const;
  Array const &GetArray() const;
  Object const &GetObject() const;

  void SetBool(Bool const &value);
  void SetNumber(Double const &value);
  void SetString(Str const &value);
  void SetArray(Array const &value);
  void SetObject(Object const &value);

  Bool IsNull() const { return mType == DataType::NULL_TYPE; }
  Bool IsBool() const { return mType == DataType::BOOL_TYPE; }
  Bool IsNumber() const { return mType == DataType::NUMBER_TYPE; }
  Bool IsString() const { return mType == DataType::STRING_TYPE; }
  Bool IsArray() const { return mType == DataType::ARRAY_TYPE; }
  Bool IsObject() const { return mType == DataType::OBJECT_TYPE; }

  Bool Has(Str const &key) const;
  Bool Has(Size const &index) const;
  Bool EvalAsBool() const;
  Str ToString() const;

  JsonNode &operator=(Bool const &value);
  JsonNode &operator=(Double const &value);
  JsonNode &operator=(Str const &value);
  JsonNode &operator=(Array const &value);
  JsonNode &operator=(Object const &value);
  JsonNode &operator=(JsonNode const &other);
  JsonNode &operator[](Size const &index);
  JsonNode &operator[](char const *key);

  operator Bool() const { return this->EvalAsBool(); }
  operator Double() const { return this->GetNumber(); }
  operator Str() const { return this->GetString(); }
  operator Array() const { return this->GetArray(); }
  operator Object() const { return this->GetObject(); }
};

class JsonSerializer : public Geobject {
protected:
  Stream mStream;
  Size mIndent;

protected:
  virtual Str Indent(Size const &level);
  virtual Str Escape(Byte const &chr);
  virtual Str ConvertToUnicode(Byte const &chr);
  virtual Str Serialize(JsonNode const &JsonNode, Size const &level);

public:
  static ObjectID const sOID;

public:
  JsonSerializer(Size const &indent)
      : Geobject(JsonSerializer::sOID), mIndent(indent) {}
  JsonSerializer(Size const &indent, ObjectID const &oid)
      : Geobject(oid), mIndent(indent) {}

  virtual Str Serialize(JsonNode const &JsonNode) {
    return this->Serialize(JsonNode, 0);
  }
};

class JsonParser : public ParserBase {
protected:
  JsonNode mNode;
  Size mDepth;

public:
  static ObjectID const sOID;

public:
  JsonParser(Str const &filename, Size const &maxDepth = 1024);
  JsonParser(Shared<IOBuffer> buffer, Size const &depth);
  ~JsonParser() override {}

  JsonNode const &GetNode() const { return mNode; }

  Bool ParseNull(JsonNode &JsonNode);
  Bool ParseBool(JsonNode &JsonNode);
  Bool ParseNumber(JsonNode &JsonNode);
  Bool ParseString(JsonNode &JsonNode);
  Bool ParseArray(JsonNode &JsonNode);
  Bool ParseObject(JsonNode &JsonNode);
  Bool Parse();
};
} // namespace Parser
} // namespace GeoFrame
