#ifndef __TERREATE_GRAPHICS_FONT_HPP__
#define __TERREATE_GRAPHICS_FONT_HPP__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

struct Character {
  Uint codepoint;
  Texture texture;
  Pair<Uint> size;
  Pair<Uint> bearing;
  Long advance;
};

class Font final : public TerreateObjectBase {
private:
  Shared<FT_Library> mLibrary;
  Shared<FT_Face> mFace;
  Uint mSize;
  Map<wchar_t, Character> mCharacters;

private:
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
  Character const &GetCharacter(wchar_t const &character);

  /*
   * @brief: Acquirer for character.
   * @param: character: character to acquire
   * @return: character
   */
  Character const &AcquireCharacter(wchar_t const &character) const;
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
  Vec<Character> AcquireCharacters(WStr const &text) const;

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

  operator Bool() const override { return mFace != nullptr; }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_FONT_HPP__
