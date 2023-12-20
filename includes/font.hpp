#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
struct Character {
    unsigned codepoint;
    Shared<Texture> texture;
    Pair<unsigned> size;
    Pair<unsigned> bearing;
    long advance;
};

class Font : public Object {
  private:
    FT_Library mLibrary;
    FT_Face mFace;
    unsigned mSize;
    Map<wchar_t, Shared<Character>> mCharacters;

  private:
    M_DISABLE_COPY_AND_ASSIGN(Font);

  public:
    /*
     * @brief: Constructor for RawFont.
     * @param: path: path to font file
     * @param: size: size of font
     */
    Font(Str const &path, unsigned const &size);
    ~Font() override;

    /*
     * @brief: Getter for character.
     * @param: character: character to get
     * @return: character
     */
    Shared<Character> const &GetCharacter(wchar_t const &character) const;
    /*
     * @brief: Getter for text size in pixels.
     * @param: text: text to get size of
     * @return: text size in pixels {width, height}
     */
    Pair<unsigned> GetTextSize(WStr const &text) const;
    /*
     * @brief: Getter for characters of the text.
     * @param: text: text to get characters of
     * @return: characters of text
     */
    Vec<Shared<Character>> GetCharacters(WStr const &text) const;
    /*
     * @brief: Getter for font size.
     * @return: font size
     */
    unsigned GetFontSize() const { return mSize; }

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
};
} // namespace GeoFrame
