#include "buffer.h"

namespace GeoFrame {
	std::string GL2STRING(GLenum type) {
		switch (type) {
		case GL_BYTE:
			return "GL_BYTE";
		case GL_UNSIGNED_BYTE:
			return "GL_UNSIGNED_BYTE";
		case GL_SHORT:
			return "GL_SHORT";
		case GL_UNSIGNED_SHORT:
			return "GL_UNSIGNED_SHORT";
		case GL_INT:
			return "GL_INT";
		case GL_UNSIGNED_INT:
			return "GL_UNSIGNED_INT";
		case GL_HALF_FLOAT:
			return "GL_HALF_FLOAT";
		case GL_FLOAT:
			return "GL_FLOAT";
		case GL_DOUBLE:
			return "GL_DOUBLE";
		default:
			return "Error-Type";
		}
	}


	Attribute::Attribute() : mType(GL_FLOAT), mComponents(-1), mStride(-1), mOffset(-1) { ; }

	Attribute::Attribute(const Attribute& attr)
		: mType(attr.mType), mComponents(attr.mComponents), mStride(attr.mStride), mOffset(attr.mOffset) {
		;
	}

	Attribute::Attribute(GLenum type, GLsizei components) : mType(type), mComponents(components), mStride(-1), mOffset(-1) { ; }

	Attribute::Attribute(GLenum type, GLsizei components, GLsizei stride, GLsizei offset)
		: mType(type), mComponents(components), mStride(stride), mOffset(offset) {
		;
	}

	Buffer::Buffer(GLenum usage) : mUsage(usage) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);
	}

	Buffer::Buffer(size_t vertexBufferSize, size_t indexBufferSize, GLenum usage) : mUsage(usage) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, usage);
		if (indexBufferSize == -1) { ; }
		else {
			glGenBuffers(1, &mEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, usage);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	void Buffer::bind() const {
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	}

	void Buffer::unbind() const {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

std::ostream& operator<<(std::ostream& stream, const GeoFrame::Attribute& attribute) {
	stream << "attr(";
	stream << "type : " << GeoFrame::GL2STRING(attribute.mType) << ", ";
	stream << "components : " << attribute.mComponents << ", ";
	stream << "stride : " << attribute.mStride << ", ";
	stream << "offset : " << attribute.mOffset;
	stream << ")";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const GeoFrame::Buffer& buffer) {
	stream << "Buffer(" << std::endl;
	for (const auto& attr : buffer.getAttributes()) {
		stream << "    " << attr << ", " << std::endl;
	}
	stream << ")";
	return stream;
}
