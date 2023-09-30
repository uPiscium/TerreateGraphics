#include "shader.h"

namespace GeoFrame {
	Source::Source(GLenum sourceType) : mType(sourceType) {
		mID = glCreateShader(sourceType);
	}

	Source::Source(GLenum sourceType, const std::string& source) : mSource(source), mType(sourceType) {
		mID = glCreateShader(sourceType);
	}

	GLenum Source::GetType() const { return mType; }

	unsigned Source::GetID() const { return mID; }

	std::string Source::GetLog() const { return mLog; }

	bool Source::IsComplied() const { return mCompiled; }

	void Source::LoadSourceFile(const std::string& filePath) {
		std::ifstream file;
		file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		try {
			file.open(filePath.c_str());
			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();
			mSource = buffer.str();
		}
		catch (std::ifstream::failure e) {
			mSource = "";
		}
	}

	void Source::LoadBuffer(const std::string& buffer) { mSource = buffer; }

	void Source::LoadBuffer(const std::stringstream& buffer) { mSource = buffer.str(); }

	void Source::LoadBuffer(const char* buffer) { mSource = std::string(buffer); }

	void Source::Compile() {
		const char* ptr = mSource.c_str();
		glShaderSource(mID, 1, &ptr, NULL);
		glCompileShader(mID);

		int status;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &status);
		if (!status) {
			char log[1024];
			glGetShaderInfoLog(mID, 1024, NULL, log);
			mLog = std::string(log);
		}
		else {
			mLog = "NO ERROR";
			mCompiled = true;
		}
	}


	Source Source::FromFile(GLenum sourceType, const std::string& filePath) {
		Source source(sourceType);
		source.LoadSourceFile(filePath.c_str());
		return source;
	}

	Source Source::FromBuffer(GLenum sourceType, const std::string& buffer) {
		Source source(sourceType);
		source.LoadBuffer(buffer);
		return source;
	}

	Source Source::FromBuffer(GLenum sourceType, const std::stringstream& buffer) {
		Source source(sourceType);
		source.LoadBuffer(buffer.str());
		return source;
	}

	Source Source::FromBuffer(GLenum sourceType, const char* buffer) {
		std::string buf(buffer);
		Source source(sourceType);
		source.LoadBuffer(buf);
		return source;
	}


	Program::Program() { mID = glCreateProgram(); }

	Program::Program(Source vertexSource, Source fragmentSource) {
		mID = glCreateProgram();

		if (!vertexSource.IsComplied()) {
			vertexSource.Compile();
		}
		else { ; }

		if (vertexSource.IsComplied()) {
			glAttachShader(mID, vertexSource.GetID());
			mVertexAttached = true;
		}
		else {
			mVertexAttached = false;
		}

		if (!fragmentSource.IsComplied()) {
			fragmentSource.Compile();
		}
		else { ; }

		if (fragmentSource.IsComplied()) {
			glAttachShader(mID, fragmentSource.GetID());
			mFragmentAttached = true;
		}
		else {
			mFragmentAttached = false;
		}
	}

	Program::Program(Source vertexSource, Source geometrySource, Source fragmentSource) {
		mID = glCreateProgram();

		if (!vertexSource.IsComplied()) {
			vertexSource.Compile();
		}
		else { ; }

		if (vertexSource.IsComplied()) {
			glAttachShader(mID, vertexSource.GetID());
			mVertexAttached = true;
		}
		else {
			mVertexAttached = false;
		}

		if (!geometrySource.IsComplied()) {
			geometrySource.Compile();
		}
		else { ; }

		if (geometrySource.IsComplied()) {
			glAttachShader(mID, geometrySource.GetID());
			mGeometryAttached = true;
		}
		else { ; }

		if (!fragmentSource.IsComplied()) {
			fragmentSource.Compile();
		}
		else { ; }

		if (fragmentSource.IsComplied()) {
			glAttachShader(mID, fragmentSource.GetID());
			mFragmentAttached = true;
		}
		else {
			mFragmentAttached = false;
		}
	}

	unsigned Program::GetID() const { return mID; }

	std::string Program::GetLog() const { return mLog; }

	bool Program::IsCompiled() const { return mCompiled; }

	void Program::AttachSource(Source source) {
		switch (source.GetType()) {
		case GL_VERTEX_SHADER:
			glAttachShader(mID, source.GetID());
			mVertexAttached = true;
		case GL_FRAGMENT_SHADER:
			glAttachShader(mID, source.GetID());
			mFragmentAttached = true;
		case GL_GEOMETRY_SHADER:
			glAttachShader(mID, source.GetID());
			mGeometryAttached = true;
		default:
			throw ShaderTypeError("Unknown shader type detected.");
		}
	}

	void Program::Compile() {
		if (mVertexAttached && mFragmentAttached) {
			glLinkProgram(mID);

			int status;
			glGetShaderiv(mID, GL_LINK_STATUS, &status);
			if (!status) {
				char log[1024];
				glGetProgramInfoLog(mID, 1024, NULL, log);
				mLog = std::string(log);
			}
			else {
				mLog = "NO ERROR";
				mCompiled = true;
			}
		}
	}

	void Program::Use() {
		if (!mCompiled) {
			this->Compile();
		}
		else { ; }
		glUseProgram(mID);
	}
}
