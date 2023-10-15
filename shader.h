#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "core.h"
#include "exception.h"

namespace GeoFrame {
	class Source {
	private:
		SourceType mType = SourceType::VERTEX_SHADER;
		unsigned mID = 0;
		std::string mSource = "";
		std::string mLog = "";
		bool mCompiled = false;

	public:
		Source(SourceType sourceType) : mType(sourceType) { mID = glCreateShader((GLenum)sourceType); }
		Source(SourceType sourceType, const std::string& source)
			: mSource(source), mType(sourceType)
		{
			mID = glCreateShader((GLenum)sourceType);
		}

		const SourceType& GetType() const { return mType; }
		const unsigned& GetID() const { return mID; }
		const std::string& GetLog() const { return mLog; }

		const bool& IsComplied() const { return mCompiled; }

		void LoadSourceFile(const std::string& filePath);
		void LoadBuffer(const std::string& buffer) { mSource = buffer; }
		void LoadBuffer(const std::stringstream& buffer) { mSource = buffer.str(); }
		void LoadBuffer(const char* buffer) { mSource = std::string(buffer); }
		void Compile();

	public:
		static Source FromFile(SourceType sourceType, const std::string& filePath);
		static Source FromBuffer(SourceType sourceType, const std::string& buffer);
		static Source FromBuffer(SourceType sourceType, const std::stringstream& buffer);
		static Source FromBuffer(SourceType sourceType, const char* buffer);
	};

	class Program {
	private:
		unsigned mID = 0;
		bool mVertexAttached = false;
		bool mGeometryAttached = false;
		bool mFragmentAttached = false;
		std::string mLog = "";
		bool mLinked = false;

	public:
		Program() { mID = glCreateProgram(); }
		Program(Source vertexSource, Source fragmentSource);
		Program(Source vertexSource, Source geometrySource, Source fragmentSource);

		unsigned GetLocation(std::string name) const { return glGetUniformLocation(mID, name.c_str()); }
		const unsigned& GetID() const { return mID; }
		const std::string& GetLog() const { return mLog; }

		void SetBoolean(std::string name, bool value);
		void SetBoolean(std::string name, bool v1, bool v2);
		void SetBoolean(std::string name, bool v1, bool v2, bool v3);
		void SetBoolean(std::string name, bool v1, bool v2, bool v3, bool v4);
		void SetBooleanArray(std::string name, std::vector<bool> values);
		void SetBooleanArray(std::string name, size_t size, bool* values);
		void SetInteger(std::string name, int value);
		void SetInteger(std::string name, int v1, int v2);
		void SetInteger(std::string name, int v1, int v2, int v3);
		void SetInteger(std::string name, int v1, int v2, int v3, int v4);
		void SetIntegerArray(std::string name, std::vector<int> values);
		void SetIntegerArray(std::string name, size_t size, int* values);
		void SetUnsigned(std::string name, unsigned value);
		void SetUnsigned(std::string name, unsigned v1, unsigned v2);
		void SetUnsigned(std::string name, unsigned v1, unsigned v2, unsigned v3);
		void SetUnsigned(std::string name, unsigned v1, unsigned v2, unsigned v3, unsigned v4);
		void SetUnsignedArray(std::string name, std::vector<unsigned> values);
		void SetUnsignedArray(std::string name, size_t size, unsigned* values);
		void SetFloat(std::string name, float value);
		void SetFloat(std::string name, float v1, float v2);
		void SetFloat(std::string name, float v1, float v2, float v3);
		void SetFloat(std::string name, float v1, float v2, float v3, float v4);
		void SetFloatArray(std::string name, std::vector<float> values);
		void SetFloatArray(std::string name, size_t size, float* values);
		void SetMatrix2x2(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix2x2(std::string name, bool transpose, float* value);
		void SetMatrix2x3(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix2x3(std::string name, bool transpose, float* value);
		void SetMatrix2x4(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix2x4(std::string name, bool transpose, float* value);
		void SetMatrix3x2(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix3x2(std::string name, bool transpose, float* value);
		void SetMatrix3x3(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix3x3(std::string name, bool transpose, float* value);
		void SetMatrix3x4(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix3x4(std::string name, bool transpose, float* value);
		void SetMatrix4x2(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix4x2(std::string name, bool transpose, float* value);
		void SetMatrix4x3(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix4x3(std::string name, bool transpose, float* value);
		void SetMatrix4x4(std::string name, bool transpose, std::vector<float> value);
		void SetMatrix4x4(std::string name, bool transpose, float* value);

		const bool& IsLinked() const { return mLinked; }

		void AttachSource(Source source);
		void Link();
		void Use() const;
	};
}
