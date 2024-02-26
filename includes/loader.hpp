#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Parser {
class IOBuffer {
public:
  using Iter = Str::iterator;

protected:
  Iter mBegin;
  Iter mEnd;
  Iter mCursor;
  Uint mLine;

public:
  IOBuffer(Iter const &begin, Iter const &end)
      : mBegin(begin), mEnd(end), mCursor(begin), mLine(1) {}
  ~IOBuffer() = default;

  Byte GetChar();
  Str GetWord();
  Iter const &GetBegin() const { return mBegin; }
  Iter const &GetEnd() const { return mEnd; }
  Iter const &GetCursor() const { return mCursor; }

  Iter begin() const { return mBegin; }
  Iter end() const { return mEnd; }

  Byte FetchChar();
  Str FetchWord();
  void UngetChar();
  void UngetWord();
  void SkipWhiteSpace();
  Size Find(Byte const &chr);
  Size Find(Str const &pattern);
  Bool Match(Byte const &chr);
  Bool Match(Str const &pattern);
  Bool Except(Byte const &chr);
  Bool Except(Str const &pattern);
  void Read(Byte *buffer, Size const &size);
  void Unread(Size const &size);
  void Ignore(Size const &size);
  Str AsUnicode(Byte const &c1, Byte const &c2, Byte const &c3, Byte const &c4);

  IOBuffer &operator++();
  IOBuffer &operator--();
  IOBuffer &operator+=(Uint const &size);
  IOBuffer &operator-=(Uint const &size);
};

class Node {
public:
  using Array = Vec<Node>;
  using Object = Map<Str, Node>;

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
  Node() : mType(DataType::NULL_TYPE) {}
  explicit Node(Bool const &value) : mType(DataType::BOOL_TYPE) {
    mStorage.mBool = value;
  }
  explicit Node(Double const &value) : mType(DataType::NUMBER_TYPE) {
    mStorage.mNumber = value;
  }
  explicit Node(Str const &value) : mType(DataType::STRING_TYPE) {
    mStorage.mString = new Str(value);
  }
  explicit Node(Array const &value) : mType(DataType::ARRAY_TYPE) {
    mStorage.mArray = new Array(value);
  }
  explicit Node(Object const &value) : mType(DataType::OBJECT_TYPE) {
    mStorage.mObject = new Object(value);
  }
  explicit Node(char const *value) : mType(DataType::STRING_TYPE) {
    mStorage.mString = new Str(value);
  }
  Node(DataType const &type);
  Node(char const *value, Size const &size) : mType(DataType::STRING_TYPE) {
    mStorage.mString = new Str(value, size);
  }
  Node(Node const &other);
  ~Node() { this->Erase(); }

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

  Node &operator=(Bool const &value);
  Node &operator=(Double const &value);
  Node &operator=(Str const &value);
  Node &operator=(Array const &value);
  Node &operator=(Object const &value);
  Node &operator=(Node const &other);
  Node &operator[](Size const &index);
  Node &operator[](Str const &key);

  operator Bool() const { return this->EvalAsBool(); }
  operator Double() const { return this->GetNumber(); }
  operator Str() const { return this->GetString(); }
  operator Array() const { return this->GetArray(); }
  operator Object() const { return this->GetObject(); }
};

class Serializer : public Geobject {
protected:
  Stream mStream;
  Size mIndent;

protected:
  virtual Str Indent(Size const &level);
  virtual Str Escape(Byte const &chr);
  virtual Str ConvertToUnicode(Byte const &chr);
  virtual Str Serialize(Node const &node, Size const &level);

public:
  static ObjectID const sOID;

public:
  Serializer(Size const &indent)
      : Geobject(Serializer::sOID), mIndent(indent) {}
  Serializer(Size const &indent, ObjectID const &oid)
      : Geobject(oid), mIndent(indent) {}

  virtual Str Serialize(Node const &node) { return this->Serialize(node, 0); }
};

class ParserBase : public Geobject {
protected:
  Shared<IOBuffer> mBuffer;

public:
  static ObjectID const sOID;

public:
  ParserBase(Str const &filename);
  ParserBase(Shared<IOBuffer> buffer)
      : Geobject(ParserBase::sOID), mBuffer(buffer) {}
  ParserBase(ObjectID const &oid, Str const &filename);
  ParserBase(ObjectID const &oid, Shared<IOBuffer> buffer)
      : Geobject(oid), mBuffer(buffer) {}
  virtual ~ParserBase() override {}
};

class JsonParser : public ParserBase {
protected:
  Node mRoot;
  Size mDepth;

public:
  static ObjectID const sOID;

public:
  JsonParser(Str const &filename, Size const &maxDepth = 1024);
  JsonParser(Shared<IOBuffer> buffer, Size const &depth);
  ~JsonParser() override;

  Node const &GetRoot() const { return mRoot; }

  Bool ParseNull(Node &node);
  Bool ParseBool(Node &node);
  Bool ParseNumber(Node &node);
  Bool ParseString(Node &node);
  Bool ParseArray(Node &node);
  Bool ParseObject(Node &node);
  Bool Parse();
};
} // namespace Parser

namespace Loader {
class Material final : public Geobject {
private:
  Str mName;
  Map<MaterialTexture, Shared<Core::Texture>> mTextures;
  Map<MaterialColor, vec3> mColors;
  Map<MaterialConstant, Float> mConstants;

public:
  static ObjectID const sOID;

public:
  Material(Str const &name) : Geobject(Material::sOID), mName(name) {}
  Material(Material const &other)
      : Geobject(Material::sOID), mName(other.mName),
        mTextures(other.mTextures), mColors(other.mColors),
        mConstants(other.mConstants) {}

  Str const &GetName() const { return mName; }
  Shared<Core::Texture> const &GetTexture(MaterialTexture const &type) const;
  vec3 const &GetColor(MaterialColor const &type) const;
  Float const &GetConstant(MaterialConstant const &type) const;

  void SetName(Str const &name) { mName = name; }
  void SetTexture(MaterialTexture const &type,
                  Shared<Core::Texture> const &texture);
  void SetColor(MaterialColor const &type, vec3 const &color);
  void SetConstant(MaterialConstant const &type, Float const &constant);

  Bool HasTexture(MaterialTexture const &type) const;
  Bool HasColor(MaterialColor const &type) const;
  Bool HasConstant(MaterialConstant const &type) const;

  Shared<Core::Texture> const &operator[](MaterialTexture const &type) const;
  vec3 const &operator[](MaterialColor const &type) const;
  Float const &operator[](MaterialConstant const &type) const;
};

class LoaderBase : public Geobject {
private:
  Str mFilename;
  Str mExtension;
  Vec<vec3> mVertices;
  Vec<vec3> mNormals;
  Vec<vec2> mUVs;

public:
  static ObjectID const sOID;

public:
  LoaderBase() : Geobject(LoaderBase::sOID) {}
  LoaderBase(Str const &filename, ObjectID const &oid)
      : Geobject(oid), mFilename(filename) {
    mExtension = mFilename.substr(mFilename.find_last_of(".") + 1);
  }
  virtual ~LoaderBase() override {}

  Str const &GetFilename() const { return mFilename; }
  Str const &GetExtension() const { return mExtension; }
  Vec<vec3> const &GetVertices() const { return mVertices; }
  Vec<vec3> const &GetNormals() const { return mNormals; }
  Vec<vec2> const &GetUVs() const { return mUVs; }
};
} // namespace Loader
} // namespace GeoFrame
