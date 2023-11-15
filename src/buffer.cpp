#include "../includes/buffer.hpp"

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

	std::pair<size_t, std::vector<size_t>> VertexArray::GetAttributeDatas(const std::vector<Attribute>& attrs) {
		std::vector<size_t> offsets = {};
		size_t currentOffset = 0, strideSize = 0;
		if (attrs[0].mStride == -1 || attrs[0].mOffset == -1) {
			for (unsigned i = 0; i < attrs.size(); i++) {
				const Attribute& attr = attrs[i];
				offsets.push_back(currentOffset);
				currentOffset += GetSize(attr.mType) * attr.mComponents;
				strideSize += attr.mComponents * GetSize(attr.mType);
			}
		}
		
		return std::pair<size_t, std::vector<size_t>>(strideSize, offsets);
	}

	void VertexArray::Draw(DrawMode mode) {
		glBindVertexArray(mID);
		if (mIndices != 0) {
			glDrawElements((GLenum)mode, mIndices, (GLenum)mIndexType, NULL);
		}
		else {
			throw IndexBufferError("No index buffer is binded.");
		}
		glBindVertexArray(0);
	}

	void VertexArray::DrawInstances(size_t numOfInstances, DrawMode mode) {
		glBindVertexArray(mID);
		if (mIndices != 0) {
			glDrawElementsInstanced((GLenum)mode, mIndices, (GLenum)mIndexType, NULL, numOfInstances);
		}
		else {
			throw IndexBufferError("No index buffer is binded.");
		}
		glBindVertexArray(0);
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
