#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "exception.h"

namespace GeoFrame {
	struct Source {
	private:
		GLenum mType = 0;
		unsigned mID = 0;
		std::string mSource = "";
		std::string mLog = "";
		bool mCompiled = false;

	public:
		Source(GLenum sourceType);
		Source(GLenum sourceType, const std::string& source);

		GLenum GetType() const;
		unsigned GetID() const;
		std::string GetLog() const;

		bool IsComplied() const;

		void LoadSourceFile(const std::string& filePath);
		void LoadBuffer(const std::string& buffer);
		void LoadBuffer(const std::stringstream& buffer);
		void LoadBuffer(const char* buffer);
		void Compile();

	public:
		static Source FromFile(GLenum sourceType, const std::string& filePath);
		static Source FromBuffer(GLenum sourceType, const std::string& buffer);
		static Source FromBuffer(GLenum sourceType, const std::stringstream& buffer);
		static Source FromBuffer(GLenum sourceType, const char* buffer);
	};

	struct Program {
	private:
		unsigned mID = 0;
		bool mVertexAttached = false;
		bool mGeometryAttached = false;
		bool mFragmentAttached = false;
		std::string mLog = "";
		bool mCompiled = false;

	public:
		Program();
		Program(Source vertexSource, Source fragmentSource);
		Program(Source vertexSource, Source geometrySource, Source fragmentSource);

		unsigned GetID() const;
		std::string GetLog() const;

		bool IsCompiled() const;

		void AttachSource(Source source);
		void Compile();
		void Use();
	};
}
