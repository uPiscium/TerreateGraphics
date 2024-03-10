#pragma once
#include "../defines.hpp"
#include "../exceptions.hpp"
#include "../object.hpp"
#include "../texture.hpp"

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

class ParserBase : public Geobject {
protected:
  Str mFiledata;
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
} // namespace Parser
} // namespace GeoFrame
