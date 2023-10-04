#include "buffer.h"

namespace GeoFrame {
	GLType TYPE2GL(const type_info& type) {
		if (type == typeid(char)) {
			return GLType::BYTE;
		}
		else if (type == typeid(unsigned char)) {
			return GLType::UNSIGNED_BYTE;
		}
		else if (type == typeid(short)) {
			return GLType::SHORT;
		}
		else if (type == typeid(unsigned short)) {
			return GLType::UNSIGNED_SHORT;
		}
		else if (type == typeid(int)) {
			return GLType::INT;
		}
		else if (type == typeid(unsigned)) {
			return GLType::UNSIGNED_INT;
		}
		else if (type == typeid(float)) {
			return GLType::FLOAT;
		}
		else if (type == typeid(double)) {
			return GLType::DOUBLE;
		}
		else {
			return GLType::HALF_FLOAT;
		}
	}

	std::string GL2STRING(GLType type) {
		switch (type) {
		case GLType::BYTE:
			return "GL_BYTE";
		case GLType::UNSIGNED_BYTE:
			return "GL_UNSIGNED_BYTE";
		case GLType::SHORT:
			return "GL_SHORT";
		case GLType::UNSIGNED_SHORT:
			return "GL_UNSIGNED_SHORT";
		case GLType::INT:
			return "GL_INT";
		case GLType::UNSIGNED_INT:
			return "GL_UNSIGNED_INT";
		case GLType::HALF_FLOAT:
			return "GL_HALF_FLOAT";
		case GLType::FLOAT:
			return "GL_FLOAT";
		case GLType::DOUBLE:
			return "GL_DOUBLE";
		case GLType::DOUBLE_BYTE:
			return "GL_2_BYTE";
		case GLType::TRIPLE_BYTE:
			return "GL_3_BYTE";
		case GLType::QUAD_BYTE:
			return "GL_4_BYTE";
		default:
			return "Error-Type";
		}
	}

	size_t GetSize(GLType type) {
		switch (type) {
		case GLType::BYTE:
			return sizeof(char);
		case GLType::UNSIGNED_BYTE:
			return sizeof(unsigned char);
		case GLType::SHORT:
			return sizeof(short);
		case GLType::UNSIGNED_SHORT:
			return sizeof(unsigned short);
		case GLType::INT:
			return sizeof(int);
		case GLType::UNSIGNED_INT:
			return sizeof(unsigned);
		case GLType::HALF_FLOAT:
			return sizeof(float) / 2;
		case GLType::FLOAT:
			return sizeof(float);
		case GLType::DOUBLE:
			return sizeof(double);
		case GLType::DOUBLE_BYTE:
			return sizeof(char) * 2;
		case GLType::TRIPLE_BYTE:
			return sizeof(char) * 3;
		case GLType::QUAD_BYTE:
			return sizeof(char) * 4;
		default:
			return 0;
		}
	}


	Attribute::Attribute() : mType(GLType::FLOAT), mComponents(-1), mStride(-1), mOffset(-1) { ; }

	Attribute::Attribute(GLType type, GLsizei components) : mType(type), mComponents(components), mStride(-1), mOffset(-1) { ; }

	Attribute::Attribute(GLType type, GLsizei components, GLsizei stride, GLsizei offset)
		: mType(type), mComponents(components), mStride(stride), mOffset(offset) {
		;
	}

	void Attribute::SetDivisor(unsigned divisor) { mDivisor = divisor; }

	Buffer::Buffer(BufferUsage usage) : mUsage(usage) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(size_t vertexBufferSize, size_t indexBufferSize, BufferUsage usage) : mUsage(usage) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, (GLenum)usage);
		if (indexBufferSize != -1) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, (GLenum)usage);
		}
		else { ; }

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	std::vector<Attribute> Buffer::GetAttributes() const { return mAttributes; }

	void Buffer::SetAttribute(Attribute attr) { mAttributes.push_back(attr); }

	void Buffer::Compile() {
		std::vector<size_t> offsets = {};
		size_t currentOffset = 0, totalComps = 0;
		if (mAttributes[0].mStride == -1 || mAttributes[0].mOffset == -1) {
			for (unsigned i = 0; i < mAttributes.size(); i++) {
				Attribute& attr = mAttributes[i];
				offsets.push_back(currentOffset);
				currentOffset += GetSize(attr.mType) * attr.mComponents;
				totalComps += attr.mComponents;
			}
		}
		else { ; }

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		for (unsigned i = 0; i < mAttributes.size(); i++) {
			Attribute& attr = mAttributes[i];
			size_t stride, offset;
			if (attr.mStride == -1) {
				stride = totalComps;
			}
			else {
				stride = attr.mStride;
			}

			if (attr.mOffset == -1) {
				offset = offsets[i];
			}
			else {
				offset = attr.mOffset;
			}

			if (attr.mDivisor != -1) {
				glVertexAttribDivisor(i, attr.mDivisor);
			}
			else { ; }

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i, attr.mComponents,
				(GLenum)attr.mType, GL_FALSE, stride, (void*)offset
			);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		mCompiled = true;
	}

	void Buffer::Bind() const { glBindVertexArray(mVAO); }

	void Buffer::Unbind() const { glBindVertexArray(0); }

	void Buffer::Draw(DrawMode drawMode) {
		if (!mCompiled) {
			this->Compile();
		}
		else { ; }

		this->Bind();
		glDrawElements((GLenum)drawMode, mIndices, (GLenum)mIndexType, NULL);
		this->Unbind();
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
	for (const auto& attr : buffer.GetAttributes()) {
		stream << "    " << attr << ", " << std::endl;
	}
	stream << ")";
	return stream;
}
