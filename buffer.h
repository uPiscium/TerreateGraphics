#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include "core.h"

namespace GeoFrame {
	GLType TYPE2GL(const type_info& type);
	std::string GL2STRING(GLType type);
	size_t GetSize(GLType type);

	class Attribute {
	public:
		GLType mType = GLType::FLOAT;
		int mComponents = 0;
		int mStride = 0;
		int mOffset = 0;
		int mDivisor = -1;

	public:
		Attribute();
		/*
		* Attribute definition class.
		[params]
		* type : Component type of the attribute.
		* components : Number of components of the attribute.
		*/
		Attribute(GLType type, GLsizei components);
		/*
		* Attribute definition class.
		[params]
		* type : Component type of the attribute.
		* components : Number of components of the attribute.
		* stride : Stride of this attribute.
		* offset : Offset of this attribute.
		*/
		Attribute(GLType type, GLsizei components, GLsizei stride, GLsizei offset);
		/*
		* Set attribute divisor.
		[params]
		* divisor : Specify how many vertices to divide the data into.
		*/
		void SetDivisor(unsigned divisor);
	};

	class Buffer {
	private:
		BufferUsage mUsage = BufferUsage::STATIC_DRAW;
		unsigned mVAO = 0;
		unsigned mVBO = 0;
		unsigned mEBO = 0;
		std::vector<Attribute> mAttributes = {};
		bool mCompiled = false;
		size_t mIndices = 0;
		GLType mIndexType = GLType::UNSIGNED_INT;

	public:
		/*
		* Vertex buffer creation class.
		[params]
		* usage : Usage of this buffer.
		*/
		Buffer(BufferUsage usage = BufferUsage::STATIC_DRAW);
		/*
		* Vertex buffer creation class.
		[params]
		* vertexBufferSize : The whole size of vertex buffer data.
		* indexBufferSize : The whole size of index buffer data. If "-1", buffer will allocate in SetIndexData() or SetBufferDatas().
		* usage : Usage of this buffer.
		*/
		Buffer(size_t vertexBufferSize, size_t indexBufferSize = -1, BufferUsage usage = BufferUsage::STATIC_DRAW);

		/*
		* Vertex attribute list getter.
		[returns]
		* @ : Vertex attribute list.
		*/
		std::vector<Attribute> GetAttributes() const;

		/*
		* Add new attribute.
		[params]
		* attr : Attribute to add.
		*/
		void SetAttribute(Attribute attr);
		/*
		* Set vertex buffer data.
		[params]
		* data : Vertex buffer data.
		*/
		template<typename T>
		void SetVertexBufferData(std::vector<T> data) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], (GLenum)mUsage);
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		/*
		* Rewrite vertex buffer data.
		[params]
		* data : New buffer data.
		* offset : Offset of new data.
		[WARNING]
		* Call non offset version before calling this.
		* The template type <T> must be the same as written data type.
		* Data size must be less than written data size.
		*/
		template<typename T>
		void SetVertexBufferData(std::vector<T> data, size_t offset) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(T) * data.size(), &data[0]);
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		/*
		* Set index buffer data.
		[params]
		* data : Index buffer data.
		*/
		template<typename T>
		void SetIndexBufferData(std::vector<T> data) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			mIndexType = TYPE2GL(typeid(T));
			mIndices = data.size();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], (GLenum)mUsage);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/*
		* Rewrite index buffer data.
		[params]
		* data :  New index buffer data.
		* offset : Offset of new data.
		[WARNING]
		* Call non offset version before calling this.
		* The template type <T> must be the same as written data type.
		* Data size must be less than written data size.
		*/
		template<typename T>
		void SetIndexBufferData(std::vector<T> data, size_t offset) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(T) * data.size(), &data[0]);
			
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/*
		* Set vertex and index buffer data.
		[params]
		* vertexBufferData : Vertex buffer data.
		* indexBufferData : Index buffer data.
		*/
		template<typename S, typename T>
		void SetBufferDatas(std::vector<S> vertexBufferData, std::vector<T> indexBufferData) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

			mIndexType = TYPE2GL(typeid(T));
			mIndices = indexBufferData.size();
			
			glBufferData(GL_ARRAY_BUFFER, sizeof(S) * vertexBufferData.size(), &vertexBufferData[0], (GLenum)mUsage);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * indexBufferData.size(), &indexBufferData[0], (GLenum)mUsage);
			
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/*
		* Rewrite vertex and index buffer data.
		[params]
		* vertexBufferData : New vertex buffer data.
		* indexBufferData : New index buffer data.
		* vertexDataOffset : Offset of new vertex data.
		* indexDataOffset : Offset of new index data.
		[WARNING]
		* Call non offset version before calling this.
		* The template type <T> must be the same as written data type.
		* Data size must be less than written data size.
		*/
		template<typename S, typename T>
		void SetBufferDatas(std::vector<S> vertexBufferData, std::vector<T> indexBufferData, size_t vertexDataOffset, size_t indexDataOffset) {
			glBindVertexArray(mVAO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

			glBufferSubData(GL_ARRAY_BUFFER, vertexDataOffset, sizeof(S) * vertexBufferData.size(), &vertexBufferData[0]);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexDataOffset, sizeof(T) * indexBufferData.size(), &indexBufferData[0]);
			
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/*
		* Compile buffer. Call before drawing.
		*/
		void Compile();
		/*
		* Bind all buffers.
		*/
		void Bind() const;
		/*
		* Unbind all buffers.
		*/
		void Unbind() const;
		/*
		* Draw buffer.
		*/
		void Draw(DrawMode drawMode = DrawMode::TRIANGLES);

		operator std::vector<Attribute>() const { return mAttributes; }
	};
}

std::ostream& operator<<(std::ostream& stream, const GeoFrame::Attribute& attribute);
std::ostream& operator<<(std::ostream& stream, const GeoFrame::Buffer& buffer);
