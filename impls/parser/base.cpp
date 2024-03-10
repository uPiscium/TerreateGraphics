#include "../../includes/parser/base.hpp"

namespace GeoFrame {
namespace Parser {
ObjectID const ParserBase::sOID = ObjectID("PARSER_BASE");

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

ParserBase::ParserBase(Str const &filename) : Geobject(ParserBase::sOID) {
  std::ifstream file;
  file.open(filename, std::ios::in | std::ios::binary);
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
} // namespace Parser
} // namespace GeoFrame
