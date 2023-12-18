#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../defines.hpp"
#include "rawObject.hpp"
#include "rawTexture.hpp"

namespace GeoFrame {
namespace Kernel {
struct Character {
    unsigned codepoint;
    Unique<RawTexture> texture;
    Pair<unsigned> size;
    Pair<unsigned> bearing;
    long advance;
};

class RawFont : public RawObject {
  private:
    FT_Library mLibrary;
    FT_Face mFace;
    unsigned mSize;
    Map<wchar_t, Unique<Character>> mCharacters;

  private:
    M_DISABLE_COPY_AND_ASSIGN(RawFont);

  public:
    /*
     * @brief: Constructor for RawFont.
     * @param: path: path to font file
     * @param: size: size of font
     */
    RawFont(Str const &path, unsigned const &size);
    ~RawFont() override;

    /*
     * @brief: Getter for character.
     * @param: character: character to get
     * @return: character
     */
    Character const *const GetCharacter(wchar_t const &character) const;
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
    Vec<Character const *> GetCharacters(WStr const &text) const;
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
} // namespace Kernel
} // namespace GeoFrame
