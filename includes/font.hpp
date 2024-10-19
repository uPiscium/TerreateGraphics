#ifndef __TERREATE_GRAPHICS_FONT_HPP__
#define __TERREATE_GRAPHICS_FONT_HPP__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

struct CharacterData {
  Uint codepoint;
  Pair<Uint> size;
  Pair<Uint> bearing;
  Long advance;
  Vec<Float> uv; // {x0, y0, x1, y1, z}
};

class Font : public TerreateObjectBase {
private:
  Shared<FT_Library> mLibrary = nullptr;
  Shared<FT_Face> mFace = nullptr;
  Uint mSize;
  Texture mTexture;
  Uint mXOffset = 0u;
  Uint mYOffset = 0u;
  Uint mZOffset = 0u;
  Map<wchar_t, CharacterData> mCharacters;

private:
  void InitializeTexture();
  void LoadDummyCharacter();

public:
  /*
   * @brief: Default constructor for RawFont.
   */
  Font();
  /*
   * @brief: Constructor for RawFont.
   * @param: path: path to font file
   * @param: size: size of font
   */
  Font(Str const &path, Uint const &size);
  ~Font() override;

  /*
   * @brief: Getter for font size.
   * @return: font size
   */
  Uint GetFontSize() const { return mSize; }
  /*
   * @brief: Getter for character.
   * @param: character: character to get
   * @return: character
   */
  CharacterData const &GetCharacter(wchar_t const &character);

  /*
   * @brief: Acquirer for character.
   * @param: character: character to acquire
   * @return: character
   */
  CharacterData const &AcquireCharacter(wchar_t const &character) const;
  /*
   * @brief: Acquirer for text size in pixels.
   * @param: text: text to acquire size of
   * @return: text size in pixels {width, height}
   */
  Pair<Uint> AcquireTextSize(WStr const &text) const;
  /*
   * @brief: Acquirer for characters of the text.
   * @param: text: text to acquire characters of
   * @return: characters of text
   */
  Vec<CharacterData> AcquireCharacters(WStr const &text) const;

  /*
   * @brief: Loads font data.
   * @param: path: path to font file
   * @param: size: size of font
   */
  void LoadFont(Str const &path, Uint const &size);
  /*
   * @brief: Loads character data.
   * @param: character: character to load
   */
  void LoadCharacter(wchar_t const &character);
  /*
   * @brief: Loads text into OpenGL texture.
   * @param: text: text to load
   */
  void LoadText(WStr const &text);

  /*
   * @brief: Uses font texture.
   */
  void Use() const { mTexture.Bind(); }
  /*
   * @brief: Unuses font texture.
   */
  void Unuse() const { mTexture.Unbind(); }

  operator Bool() const override { return mFace != nullptr; }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_FONT_HPP__
