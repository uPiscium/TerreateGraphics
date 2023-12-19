#include "../../includes/kernel/rawFont.hpp"

namespace GeoFrame {
namespace Kernel {
RawFont::RawFont(Str const &path, unsigned const &size) : mSize(size) {
    if (FT_Init_FreeType(&mLibrary)) {
        M_GEO_THROW(KernelError, "Failed to initialize FreeType library.");
    }

    if (FT_New_Face(mLibrary, path.c_str(), 0, &mFace)) {
        M_GEO_THROW(KernelError, "Failed to load font.");
    }

    FT_Set_Pixel_Sizes(mFace, 0, size);
}

RawFont::~RawFont() {
    FT_Done_Face(mFace);
    FT_Done_FreeType(mLibrary);

    mCharacters.clear();
}

Character const *const RawFont::GetCharacter(wchar_t const &character) const {
    auto it = mCharacters.find(character);
    if (it == mCharacters.end()) {
        M_GEO_THROW(KernelError, "Character not found.");
    }
    return it->second.get();
}

Pair<unsigned> RawFont::GetTextSize(WStr const &text) const {
    unsigned width = 0;
    unsigned height = 0;
    for (wchar_t const &character : text) {
        Character const *const c = GetCharacter(character);
        width += c->advance >> 6;
        if (c->size.second > height) {
            height = c->size.second;
        }
    }
    return {width, height};
}

Vec<Character const *> RawFont::GetCharacters(WStr const &text) const {
    Vec<Character const *> characters;
    for (wchar_t const &character : text) {
        Character const *const c = GetCharacter(character);
        characters.push_back(c);
    }
    return characters;
}

void RawFont::LoadCharacter(wchar_t const &character) {
    if (mCharacters.find(character) != mCharacters.end()) {
        return;
    }

    if ((unsigned)character == D_HALF_WIDTH_SPACE ||
        (unsigned)character == D_FULL_WIDTH_SPACE) {
        Unique<Character> c = std::make_unique<Character>();
        unsigned width =
            ((unsigned)character == D_HALF_WIDTH_SPACE) ? mSize / 2 : mSize;
        c->codepoint = (unsigned)character;
        c->texture = nullptr;
        c->size = {width, mSize};
        c->bearing = {0, 0};
        c->advance = width;

        mCharacters.insert({character, std::move(c)});
        return;
    }

    if (FT_Load_Char(mFace, character, FT_LOAD_RENDER)) {
        M_GEO_THROW(KernelError, "Failed to load glyph.");
        return;
    }

    Unique<Character> c = std::make_unique<Character>();
    c->codepoint = (unsigned)character;
    c->texture = std::make_unique<RawTexture>();
    c->texture->LoadData(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows,
                         1, mFace->glyph->bitmap.buffer);
    c->size = {mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows};
    c->bearing = {mFace->glyph->bitmap_left, mFace->glyph->bitmap_top};
    c->advance = mFace->glyph->advance.x;

    mCharacters.insert({character, std::move(c)});
}
} // namespace Kernel
} // namespace GeoFrame
