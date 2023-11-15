#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>
#include <unordered_map>

#include "core.h"
#include "exception.h"
#include "texture.h"

namespace GeoFrame {
struct Character {
    Texture charTex = Texture(0, 0, 0, 0);
    wchar_t chr = 0;
    std::pair<unsigned, unsigned> size =
        std::make_pair<unsigned, unsigned>(0, 0);
    std::pair<int, int> bearing = std::make_pair<int, int>(0, 0);
    std::pair<int, int> advance = std::make_pair<int, int>(0, 0);
    std::pair<int, int> xrange = std::make_pair<int, int>(0, 0);
    std::pair<int, int> yrange = std::make_pair<int, int>(0, 0);
};

class Font {
  private:
    FT_Library mLibrary;
    FT_Face mFace;
    int mStandard = 0;
    unsigned mSize = 0;
    std::string mPath = "";
    std::unordered_map<wchar_t, Character> mCharMap = {};
    std::string mLog = "";

  public:
    /*
    * Font managing class.
    [params]
    * path : Font file path.
    * size : Font size.
    */
    Font(const std::string &path, unsigned size);
    ~Font();

    Font(const Font &font) = delete;
    Font operator=(const Font &font) = delete;

    /*
    * Get the length of text.
    [params]
    * text : Text to get length.
    [returns]
    * std::pair<unsigned, unsigned> : first/width, second/height.
    */
    std::vector<unsigned> GetLength(const std::wstring &text);
    /*
    * Get character datas of the text.
    [params]
    * text : Text to get datas.
    [returns]
    * std::vector<Character> : Character datas.
    */
    std::vector<Character> GetTextData(const std::wstring &text);
    /*
    * Get character data.
    [params]
    * chr : Character to get character data.
    [returns]
    * const Character& : Character data.
    */
    const Character &GetCharData(wchar_t chr) { return mCharMap[chr]; }
    /*
    * Get font loading log.
    [returns]
    * const std::string& : Font status log.
    */
    const std::string &GetLog() const { return mLog; }
    /*
    * Get font size.
    [returns]
    * const unsigned& : Font size.
    */
    const unsigned &GetSize() const { return mSize; }
    const Character &operator[](wchar_t chr) { return mCharMap[chr]; }

    /*
    * Load and register character data.
    [params]
    * chr : Character to register.
    */
    void RegisterChar(wchar_t chr);
    /*
    * Load and register each character of the text.
    [params]
    * text : Text to register.
    */
    void RegisterText(const std::wstring &text);
};
} // namespace GeoFrame
