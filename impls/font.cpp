#include "../includes/font.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

void Font::LoadDummyCharacter() {
  Character chr = Character();
  chr.codepoint = 0;
  chr.texture = Texture();
  chr.size = {0, 0};
  chr.bearing = {0, 0};
  chr.advance = 0;

  mCharacters.insert({0, chr});
}

Font::Font() {
  mLibrary = Shared<FT_Library>(new FT_Library());
  if (FT_Init_FreeType(mLibrary.get())) {
    throw Exceptions::FontError("Failed to initialize FreeType.");
    return;
  }
}

Font::Font(Str const &path, Uint const &size) : mSize(size) {
  mLibrary = Shared<FT_Library>(new FT_Library());
  if (FT_Init_FreeType(mLibrary.get())) {
    throw Exceptions::FontError("Failed to initialize FreeType.");
    return;
  }
  this->LoadFont(path, size);
}

Font::~Font() {
  if (mFace.use_count() <= 1 && mLibrary.use_count() <= 1) {
    FT_Done_Face(*mFace);
    FT_Done_FreeType(*mLibrary);
    mCharacters.clear();
  }
}

Character const &Font::GetCharacter(wchar_t const &character) {
  auto it = mCharacters.find(character);
  if (it == mCharacters.end()) {
    LoadCharacter(character);
    it = mCharacters.find(character);
  }
  return it->second;
}

Character const &Font::AcquireCharacter(wchar_t const &character) const {
  auto it = mCharacters.find(character);
  if (it == mCharacters.end()) {
    return mCharacters.at(0);
  }
  return it->second;
}

Pair<Uint> Font::AcquireTextSize(WStr const &text) const {
  Uint width = 0;
  Uint height = 0;
  for (wchar_t const &character : text) {
    Character const &c = AcquireCharacter(character);
    width += c.advance >> 6;
    if (c.size.second > height) {
      height = c.size.second;
    }
  }
  return {width, height};
}

Vec<Character> Font::AcquireCharacters(WStr const &text) const {
  Vec<Character> characters;
  for (wchar_t const &character : text) {
    Character const &c = AcquireCharacter(character);
    characters.push_back(c);
  }
  return characters;
}

void Font::LoadFont(Str const &path, Uint const &size) {
  mFace = Shared<FT_Face>(new FT_Face());
  if (FT_New_Face(*mLibrary, path.c_str(), 0, mFace.get())) {
    throw Exceptions::FontError("Failed to load font.");
    return;
  }

  FT_Set_Pixel_Sizes(*mFace, 0, size);
  this->LoadDummyCharacter();
}

void Font::LoadCharacter(wchar_t const &character) {
  if (mCharacters.find(character) != mCharacters.end()) {
    return;
  }

  if ((Uint)character == TC_UNICODE_HALF_SPACE ||
      (Uint)character == TC_UNICODE_FULL_SPACE) {
    Character c = Character();
    Uint width = ((Uint)character == TC_UNICODE_HALF_SPACE) ? mSize / 2 : mSize;
    c.codepoint = (Uint)character;
    c.texture = Texture();
    c.size = {width, mSize};
    c.bearing = {0, 0};
    c.advance = width << 6;

    mCharacters.insert({character, c});
    return;
  }

  if (FT_Load_Char(*mFace, character, FT_LOAD_RENDER)) {
    throw Exceptions::FontError("Failed to load character.");
    return;
  }

  Character c = Character();
  c.codepoint = (Uint)character;
  c.texture = Texture();
  Uint width = (*mFace)->glyph->bitmap.width;
  Uint height = (*mFace)->glyph->bitmap.rows;
  c.texture.LoadData(width, height, 1, (*mFace)->glyph->bitmap.buffer);

  c.size = {width, height};
  c.bearing = {(*mFace)->glyph->bitmap_left, (*mFace)->glyph->bitmap_top};
  c.advance = (*mFace)->glyph->advance.x;

  mCharacters.insert({character, c});
}

void Font::LoadText(WStr const &text) {
  for (wchar_t const &character : text) {
    this->LoadCharacter(character);
  }
}
} // namespace TerreateGraphics::Core
