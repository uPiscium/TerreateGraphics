#include "shader.h"

namespace GeoFrame {
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


	Source Source::FromFile(SourceType sourceType, const std::string& filePath) {
		Source source(sourceType);
		source.LoadSourceFile(filePath.c_str());
		return source;
	}

	Source Source::FromBuffer(SourceType sourceType, const std::string& buffer) {
		Source source(sourceType);
		source.LoadBuffer(buffer);
		return source;
	}

	Source Source::FromBuffer(SourceType sourceType, const std::stringstream& buffer) {
		Source source(sourceType);
		source.LoadBuffer(buffer.str());
		return source;
	}

	Source Source::FromBuffer(SourceType sourceType, const char* buffer) {
		std::string buf(buffer);
		Source source(sourceType);
		source.LoadBuffer(buf);
		return source;
	}


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

	void Program::SetBoolean(std::string name, bool value) {
		int location = this->GetLocation(name);
		glUniform1i(location, value);
	}

	void Program::SetBoolean(std::string name, bool v1, bool v2) {
		int location = this->GetLocation(name);
		glUniform2i(location, v1, v2);
	}

	void Program::SetBoolean(std::string name, bool v1, bool v2, bool v3) {
		int location = this->GetLocation(name);
		glUniform3i(location, v1, v2, v3);
	}

	void Program::SetBoolean(std::string name, bool v1, bool v2, bool v3, bool v4) {
		int location = this->GetLocation(name);
		glUniform4i(location, v1, v2, v3, v4);
	}

	void Program::SetBooleanArray(std::string name, std::vector<bool> values) {
		switch (values.size()) {
		case 1:
			this->SetBoolean(name, values[0]);
			break;
		case 2:
			this->SetBoolean(name, values[0], values[1]);
			break;
		case 3:
			this->SetBoolean(name, values[0], values[1], values[2]);
			break;
		case 4:
			this->SetBoolean(name, values[0], values[1], values[2], values[3]);
			break;
		default:
			break;
		}
	}

	void Program::SetBooleanArray(std::string name, size_t size, bool* values) {
		switch (size) {
		case 1:
			this->SetBoolean(name, values[0]);
			break;
		case 2:
			this->SetBoolean(name, values[0], values[1]);
			break;
		case 3:
			this->SetBoolean(name, values[0], values[1], values[2]);
			break;
		case 4:
			this->SetBoolean(name, values[0], values[1], values[2], values[3]);
			break;
		default:
			break;
		}
	}

	void Program::SetInteger(std::string name, int value) {
		int location = this->GetLocation(name);
		glUniform1i(location, value);
	}

	void Program::SetInteger(std::string name, int v1, int v2) {
		int location = this->GetLocation(name);
		glUniform2i(location, v1, v2);
	}

	void Program::SetInteger(std::string name, int v1, int v2, int v3) {
		int location = this->GetLocation(name);
		glUniform3i(location, v1, v2, v3);
	}

	void Program::SetInteger(std::string name, int v1, int v2, int v3, int v4) {
		int location = this->GetLocation(name);
		glUniform4i(location, v1, v2, v3, v4);
	}

	void Program::SetIntegerArray(std::string name, std::vector<int> values) {
		int location = this->GetLocation(name);
		switch (values.size()) {
		case 1:
			glUniform1iv(location, 1, &values[0]);
			break;
		case 2:
			glUniform2iv(location, 1, &values[0]);
			break;
		case 3:
			glUniform3iv(location, 1, &values[0]);
			break;
		case 4:
			glUniform4iv(location, 1, &values[0]);
			break;
		default:
			break;
		}
	}

	void Program::SetIntegerArray(std::string name, size_t size, int* values) {
		int location = this->GetLocation(name);
		switch (size) {
		case 1:
			glUniform1iv(location, 1, values);
			break;
		case 2:
			glUniform2iv(location, 1, values);
			break;
		case 3:
			glUniform3iv(location, 1, values);
			break;
		case 4:
			glUniform4iv(location, 1, values);
			break;
		default:
			break;
		}
	}

	void Program::SetUnsigned(std::string name, unsigned value) {
		int location = this->GetLocation(name);
		glUniform1ui(location, value);
	}

	void Program::SetUnsigned(std::string name, unsigned v1, unsigned v2) {
		int location = this->GetLocation(name);
		glUniform2ui(location, v1, v2);
	}

	void Program::SetUnsigned(std::string name, unsigned v1, unsigned v2, unsigned v3) {
		int location = this->GetLocation(name);
		glUniform3ui(location, v1, v2, v3);
	}

	void Program::SetUnsigned(std::string name, unsigned v1, unsigned v2, unsigned v3, unsigned v4) {
		int location = this->GetLocation(name);
		glUniform4ui(location, v1, v2, v3, v4);
	}

	void Program::SetUnsignedArray(std::string name, std::vector<unsigned> values) {
		int location = this->GetLocation(name);
		switch (values.size()) {
		case 1:
			glUniform1uiv(location, 1, &values[0]);
			break;
		case 2:
			glUniform2uiv(location, 1, &values[0]);
			break;
		case 3:
			glUniform3uiv(location, 1, &values[0]);
			break;
		case 4:
			glUniform4uiv(location, 1, &values[0]);
			break;
		default:
			break;
		}
	}

	void Program::SetUnsignedArray(std::string name, size_t size, unsigned* values) {
		int location = this->GetLocation(name);
		switch (size) {
		case 1:
			glUniform1uiv(location, 1, values);
			break;
		case 2:
			glUniform2uiv(location, 1, values);
			break;
		case 3:
			glUniform3uiv(location, 1, values);
			break;
		case 4:
			glUniform4uiv(location, 1, values);
			break;
		default:
			break;
		}
	}

	void Program::SetFloat(std::string name, float value) {
		int location = this->GetLocation(name);
		glUniform1f(location, value);
	}

	void Program::SetFloat(std::string name, float v1, float v2) {
		int location = this->GetLocation(name);
		glUniform2f(location, v1, v2);
	}

	void Program::SetFloat(std::string name, float v1, float v2, float v3) {
		int location = this->GetLocation(name);
		glUniform3f(location, v1, v2, v3);
	}

	void Program::SetFloat(std::string name, float v1, float v2, float v3, float v4) {
		int location = this->GetLocation(name);
		glUniform4f(location, v1, v2, v3, v4);
	}

	void Program::SetFloatArray(std::string name, std::vector<float> values) {
		int location = this->GetLocation(name);
		switch (values.size()) {
		case 1:
			glUniform1fv(location, 1, &values[0]);
			break;
		case 2:
			glUniform2fv(location, 1, &values[0]);
			break;
		case 3:
			glUniform3fv(location, 1, &values[0]);
			break;
		case 4:
			glUniform4fv(location, 1, &values[0]);
			break;
		default:
			break;
		}
	}

	void Program::SetFloatArray(std::string name, size_t size, float* values) {
		int location = this->GetLocation(name);
		switch (size) {
		case 1:
			glUniform1fv(location, 1, values);
			break;
		case 2:
			glUniform2fv(location, 1, values);
			break;
		case 3:
			glUniform3fv(location, 1, values);
			break;
		case 4:
			glUniform4fv(location, 1, values);
			break;
		default:
			break;
		}
	}

	void Program::SetMatrix2x2(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix2fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix2x2(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix2fv(location, 1, transpose, value);
	}

	void Program::SetMatrix2x3(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix2x3fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix2x3(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix2x3fv(location, 1, transpose, value);
	}

	void Program::SetMatrix2x4(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix2x4fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix2x4(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix2x4fv(location, 1, transpose, value);
	}

	void Program::SetMatrix3x2(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix3x2fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix3x2(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix3x2fv(location, 1, transpose, value);
	}

	void Program::SetMatrix3x3(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix3fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix3x3(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix3fv(location, 1, transpose, value);
	}

	void Program::SetMatrix3x4(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix3x4fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix3x4(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix3x4fv(location, 1, transpose, value);
	}

	void Program::SetMatrix4x2(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix4x2fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix4x2(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix4x2fv(location, 1, transpose, value);
	}

	void Program::SetMatrix4x3(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix4x3fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix4x3(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix4x3fv(location, 1, transpose, value);
	}

	void Program::SetMatrix4x4(std::string name, bool transpose, std::vector<float> value) {
		int location = this->GetLocation(name);
		glUniformMatrix4fv(location, 1, transpose, &value[0]);
	}

	void Program::SetMatrix4x4(std::string name, bool transpose, float* value) {
		int location = this->GetLocation(name);
		glUniformMatrix4fv(location, 1, transpose, value);
	}

	void Program::AttachSource(Source source) {
		switch (source.GetType()) {
		case SourceType::VERTEX_SHADER:
			glAttachShader(mID, source.GetID());
			mVertexAttached = true;
		case SourceType::FRAGMENT_SHADER:
			glAttachShader(mID, source.GetID());
			mFragmentAttached = true;
		case SourceType::GEOMETRY_SHADER:
			glAttachShader(mID, source.GetID());
			mGeometryAttached = true;
		default:
			throw ShaderTypeError("Unknown shader type detected.");
		}
	}

	void Program::Link() {
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
				mLinked = true;
			}
		}
	}

	void Program::Use() {
		if (!mLinked) {
			this->Link();
		}
		else { ; }
		glUseProgram(mID);
	}
}
