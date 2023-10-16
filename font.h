#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>

#include "core.h"
#include "exception.h"
#include "texture.h"

namespace GeoFrame {
	struct Character {
		Texture charTex = Texture(0, 0, 0, 0);
		wchar_t chr = 0;
		std::pair<unsigned, unsigned> size = std::make_pair<unsigned, unsigned>(0, 0);
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
		Font(const std::string& path, unsigned size);
		~Font();

		Font(const Font& font) = delete;
		Font operator=(const Font& font) = delete;
		
		std::vector<unsigned> GetLength(const std::wstring& text);
		std::vector<Character> GetTextData(const std::wstring& text);
		const Character& GetCharData(wchar_t chr) { return mCharMap[chr]; }
		const unsigned& GetStandard() const { return mStandard; }
		const std::string& GetLog() const { return mLog; }
		const unsigned& GetSize() const { return mSize; }
		const std::unordered_map<wchar_t, Character>& GetCharMap() const { return mCharMap; }

		const Character& operator[](wchar_t chr) { return mCharMap[chr]; }
		
		void RegisterChar(wchar_t chr);
		void RegisterText(const std::wstring& text);
	};
}
