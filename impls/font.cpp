#include "../includes/font.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

void Font::LoadDummyCharacter() {
  TC_TRACE_CALL(LOCATION(Font));

  Shared<Character> chr = std::make_shared<Character>();
  chr->codepoint = 0;
  chr->texture = nullptr;
  chr->size = {0, 0};
  chr->bearing = {0, 0};
  chr->advance = 0;

  mCharacters.insert({0, chr});
}

Font::Font(Str const &path, Uint const &size) : mSize(size) {
  TC_TRACE_CALL(LOCATION(Font));

  if (FT_Init_FreeType(&mLibrary)) {
    TC_ERROR_CALL("Failed to initialize FreeType library.");
    return;
  }

  if (FT_New_Face(mLibrary, path.c_str(), 0, &mFace)) {
    TC_ERROR_CALL("Failed to load font.");
    return;
  }

  FT_Set_Pixel_Sizes(mFace, 0, size);
  this->LoadDummyCharacter();
  TC_DEBUG_CALL("Font is generated.");
}

Font::~Font() {
  TC_TRACE_CALL(LOCATION(Font));

  FT_Done_Face(mFace);
  FT_Done_FreeType(mLibrary);
  mCharacters.clear();
  TC_DEBUG_CALL("Font is deleted.");
}

Uint Font::GetFontSize() const {
  TC_TRACE_CALL(LOCATION(Font));

  return mSize;
}

Shared<Character> const &Font::GetCharacter(wchar_t const &character) {
  TC_TRACE_CALL(LOCATION(Font));

  auto it = mCharacters.find(character);
  if (it == mCharacters.end()) {
    LoadCharacter(character);
    it = mCharacters.find(character);
  }
  return it->second;
}

Shared<Character> const &
Font::AcquireCharacter(wchar_t const &character) const {
  TC_TRACE_CALL(LOCATION(Font));

  auto it = mCharacters.find(character);
  if (it == mCharacters.end()) {
    TC_ERROR_CALL("Character not found.");
    return mCharacters.at(0);
  }
  return it->second;
}

Pair<Uint> Font::AcquireTextSize(WStr const &text) const {
  TC_TRACE_CALL(LOCATION(Font));

  Uint width = 0;
  Uint height = 0;
  for (wchar_t const &character : text) {
    Shared<Character> const &c = AcquireCharacter(character);
    width += c->advance >> 6;
    if (c->size.second > height) {
      height = c->size.second;
    }
  }
  return {width, height};
}

Vec<Shared<Character>> Font::AcquireCharacters(WStr const &text) const {
  TC_TRACE_CALL(LOCATION(Font));

  Vec<Shared<Character>> characters;
  for (wchar_t const &character : text) {
    Shared<Character> const &c = AcquireCharacter(character);
    characters.push_back(c);
  }
  return characters;
}

void Font::LoadCharacter(wchar_t const &character) {
  TC_TRACE_CALL(LOCATION(Font));

  if (mCharacters.find(character) != mCharacters.end()) {
    return;
  }

  if ((Uint)character == TC_UNICODE_HALF_SPACE ||
      (Uint)character == TC_UNICODE_FULL_SPACE) {
    Shared<Character> c = std::make_shared<Character>();
    Uint width = ((Uint)character == TC_UNICODE_HALF_SPACE) ? mSize / 2 : mSize;
    c->codepoint = (Uint)character;
    c->texture = nullptr;
    c->size = {width, mSize};
    c->bearing = {0, 0};
    c->advance = width << 6;

    mCharacters.insert({character, c});
    return;
  }

  if (FT_Load_Char(mFace, character, FT_LOAD_RENDER)) {
    TC_ERROR_CALL("Failed to load glyph.");
    return;
  }

  Shared<Character> c = std::make_shared<Character>();
  c->codepoint = (Uint)character;
  c->texture = std::make_shared<Texture>();
  c->texture->LoadData(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows, 1,
                       mFace->glyph->bitmap.buffer);

  c->size = {mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows};
  c->bearing = {mFace->glyph->bitmap_left, mFace->glyph->bitmap_top};
  c->advance = mFace->glyph->advance.x;

  mCharacters.insert({character, c});
}

void Font::LoadText(WStr const &text) {
  TC_TRACE_CALL(LOCATION(Font));

  for (wchar_t const &character : text) {
    this->LoadCharacter(character);
  }
}
} // namespace TerreateCore::Core
