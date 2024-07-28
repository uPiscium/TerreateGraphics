#ifndef __TERREATE_GRAPHICS_FONT_HPP__
#define __TERREATE_GRAPHICS_FONT_HPP__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.hpp"
#include "logger.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

struct Character {
  Uint codepoint;
  Shared<Texture> texture;
  Pair<Uint> size;
  Pair<Uint> bearing;
  Long advance;
};

class Font final : public Object {
private:
  FT_Library mLibrary;
  FT_Face mFace;
  Uint mSize;
  Map<wchar_t, Shared<Character>> mCharacters;

private:
  TC_DISABLE_COPY_AND_ASSIGN(Font);

private:
  void LoadDummyCharacter();

public:
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
  Uint GetFontSize() const;
  /*
   * @brief: Getter for character.
   * @param: character: character to get
   * @return: character
   */
  Shared<Character> const &GetCharacter(wchar_t const &character);

  /*
   * @brief: Acquirer for character.
   * @param: character: character to acquire
   * @return: character
   */
  Shared<Character> const &AcquireCharacter(wchar_t const &character) const;
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
  Vec<Shared<Character>> AcquireCharacters(WStr const &text) const;

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
