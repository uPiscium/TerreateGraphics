#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <string>
#include <vector>

#include "core.h"
#include "exception.h"

namespace GeoFrame {
	struct TextureSettings {
	public:
		bool mSRGBLoading = true;
		bool mFilppedLoading = false;
		FilterType mMinFilter = FilterType::NEAREST_MIPMAP_LINEAR;
		FilterType mMagFilter = FilterType::LINEAR;
		WrappingType mWrapS = WrappingType::REPEAT;
		WrappingType mWrapT = WrappingType::REPEAT;
		WrappingType mWrapR = WrappingType::REPEAT;

	public:
		TextureSettings(
			bool sRGBLoading = true,
			bool filppedLoading = false,
			FilterType minFilter = FilterType::NEAREST_MIPMAP_LINEAR,
			FilterType magFilter = FilterType::LINEAR,
			WrappingType wrapS = WrappingType::REPEAT,
			WrappingType wrapT = WrappingType::REPEAT,
			WrappingType wrapR = WrappingType::REPEAT
		);
	};

	class Texture {
	private:
		unsigned mID = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		unsigned mChannel = 0;

	public:
		Texture(
			unsigned width, unsigned height,
			AttachmentType attachmentType = AttachmentType::COLOR,
			TextureSettings settings = TextureSettings()
		);
		Texture(std::string path,TextureSettings settings = TextureSettings());
		Texture(const std::vector<unsigned char>& color, TextureSettings settings = TextureSettings());
		Texture(
			const std::vector<unsigned char>& bitmap,
			unsigned width, unsigned height, unsigned channel,
			TextureSettings settings = TextureSettings()
		);

		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetChannel() const;

		operator unsigned() const;

		void Bind() const;
		void Unbind() const;
	};

	class CubeTexture {
	private:
		unsigned mID = 0;
		std::vector<unsigned> mWidths = {};
		std::vector<unsigned> mHeights = {};
		std::vector<unsigned> mChannels = {};

	public:
		CubeTexture(
			const std::vector<unsigned>& widths,
			const std::vector<unsigned>& heights,
			AttachmentType attachmentType = AttachmentType::COLOR,
			TextureSettings settings = TextureSettings()
		);
		CubeTexture(
			unsigned widths,
			unsigned heights,
			AttachmentType attachmentType = AttachmentType::COLOR,
			TextureSettings settings = TextureSettings()
		);
		CubeTexture(const std::vector<std::string>& paths, TextureSettings settings = TextureSettings());
		CubeTexture(const std::vector<std::vector<float>>& colors, TextureSettings settings = TextureSettings());
		CubeTexture(const std::vector<float>& color, TextureSettings settings = TextureSettings());
		CubeTexture(
			const std::vector<std::vector<unsigned char>>& bitmaps,
			const std::vector<unsigned>& widths,
			const std::vector<unsigned>& heights,
			const std::vector<unsigned>& channels,
			TextureSettings settings = TextureSettings()
		);
		CubeTexture(
			const std::vector<std::vector<unsigned char>>& bitmaps,
			unsigned width,
			unsigned height,
			unsigned channel,
			TextureSettings settings = TextureSettings()
		);

		std::vector<unsigned> GetWidths() const;
		std::vector<unsigned> GetHeights() const;
		std::vector<unsigned> GetChannels() const;

		operator unsigned() const;

		void Bind() const;
		void Unbind() const;
	};

	class Texture3D {
	private:
		unsigned mID = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		unsigned mDepth = 0;
		unsigned mChannel = 0;

	public:
		Texture3D(const std::vector<float>& color, TextureSettings settings = TextureSettings());
		Texture3D(
			const std::vector<unsigned char>& bitmap,
			unsigned width, unsigned height, unsigned depth, unsigned channel,
			TextureSettings settings = TextureSettings()
		);

		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetDepth() const;
		unsigned GetChannel() const;

		operator unsigned() const;

		void Bind() const;
		void Unbind() const;
	};
}
