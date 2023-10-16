#include "font.h"

namespace GeoFrame {
	Font::Font(const std::string& path, unsigned size) : mSize(size) {
		mCharMap.clear();

		if (FT_Init_FreeType(&mLibrary)) {
			throw FontInitializationError("Failed to initialize 'FreeType' library.");
		}

		if (FT_New_Face(mLibrary, path.c_str(), 0, &mFace)) {
			std::string msg = "Failed to load '" + path + "'.";
			throw FontInitializationError(msg);
		}

		FT_Set_Pixel_Sizes(mFace, 0, mSize);
		mStandard = 0;
	}

	Font::~Font() {
		FT_Done_Face(mFace);
		FT_Done_FreeType(mLibrary);
	}

	std::vector<unsigned> Font::GetLength(const std::wstring& text) {
		std::vector<unsigned> size = { 0,0 };
		for (wchar_t c : text) {
			this->RegisterChar(c);

			Character& temp = mCharMap[c];
			size[0] += temp.size.first;

			if (size[1] < temp.size.second) {
				size[1] = temp.size.second;
			}
		}
		return size;
	}

	std::vector<Character> Font::GetTextData(const std::wstring& text) {
		std::vector<Character> chars = {};
		for (wchar_t c : text) {
			chars.push_back(mCharMap[c]);
		}
		return chars;
	}

	void Font::RegisterChar(wchar_t chr) {
		if (FT_Load_Char(mFace, chr, FT_LOAD_RENDER)) {
			throw FontLoadingError("Character data not fonud.");
		}

		if (mCharMap.find(chr) != mCharMap.end()) {
			return;
		}
		else if (chr == L' ') {
			Character data;
			Texture map(std::vector<unsigned char>({ 0, 0, 0, 0 }));
			data.charTex = map;
			data.chr = L' ';
			data.size = std::pair<unsigned, unsigned>({ mSize / 2, mSize });
			data.bearing = std::pair<int, int>({ 0, 0 });
			data.advance = std::pair<int, int>({ (int)mSize * 32, 0 });
			data.xrange = std::pair<int, int>({ 0, (int)mSize / 2 });
			data.yrange = std::pair<int, int>({ 0, (int)mSize });

			mCharMap.insert(std::pair<wchar_t, Character>(chr, data));
		}
		else if (chr == L'Å@') {
			Character data;
			Texture map(std::vector<unsigned char>({ 0, 0, 0, 0 }));
			data.charTex = map;
			data.chr = L'Å@';

			data.size = std::pair<unsigned, unsigned>({ mSize, mSize });
			data.bearing = std::pair<int, int>({ 0, 0 });
			data.advance = std::pair<int, int>({ (int)mSize * 32, 0 });
			data.xrange = std::pair<int, int>({ 0, (int)mSize });
			data.yrange = std::pair<int, int>({ 0, (int)mSize });

			mCharMap.insert(std::pair<wchar_t, Character>(chr, data));
		}
		else {
			unsigned char* buffer = mFace->glyph->bitmap.buffer;
			unsigned width = mFace->glyph->bitmap.width;
			unsigned height = mFace->glyph->bitmap.rows;
			Character data;
			Texture map(std::vector<unsigned char>(buffer, buffer + width * height), width, height, 1);
			data.charTex = map;
			data.chr = chr;

			data.size = std::pair<unsigned, unsigned>({ width,height });
			data.bearing = std::pair<int, int>({ mFace->glyph->bitmap_left, mFace->glyph->bitmap_top });
			data.advance = std::pair<int, int>({ mFace->glyph->advance.x, mFace->glyph->advance.y });
			data.xrange = std::pair<int, int>({ mFace->bbox.xMin, mFace->bbox.xMax });
			data.yrange = std::pair<int, int>({ mFace->bbox.yMin, mFace->bbox.yMax });

			mCharMap.insert(std::pair<wchar_t, Character>(chr, data));

			if (mStandard < height) {
				mStandard = height;
			}
			else { ; }
		}
	}

	void Font::RegisterText(const std::wstring& text) {
		for (wchar_t c : text) {
			this->RegisterChar(c);
		}
	}
}