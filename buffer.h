#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

namespace GeoFrame {
	std::string GL2STRING(GLenum type);

	struct Attribute {
	public:
		GLenum mType = GL_FLOAT;
		int mComponents = 0;
		int mStride = 0;
		int mOffset = 0;

	public:
		Attribute();
		Attribute(const Attribute& attr);
		/*
		* Attribute definition class.
		[params]
		* type : Component type of the attribute.
		* components : Number of components of the attribute.
		*/
		Attribute(GLenum type, GLsizei components);
		/*
		* Attribute definition class.
		[params]
		* type : Component type of the attribute.
		* components : Number of components of the attribute.
		* stride : Stride of this attribute.
		* offset : Offset of this attribute.
		*/
		Attribute(GLenum type, GLsizei components, GLsizei stride, GLsizei offset);
	};

	struct Buffer {
	private:
		GLenum mUsage = GL_STATIC_DRAW;
		unsigned mVAO = 0;
		unsigned mVBO = 0;
		unsigned mEBO = 0;
		std::vector<Attribute> mAttributes = {};

	public:
		/*
		* Vertex buffer creation class.
		[params]
		* usage : Usage of this buffer. [GL_STATIC_DRAW]
		*/
		Buffer(GLenum usage = GL_STATIC_DRAW);
		/*
		* Vertex buffer creation class.
		[params]
		* vertexBufferSize : The whole size of vertex buffer data.
		* indexBufferSize : The whole size of index buffer data.
		* usage : Usage of this buffer. [GL_STATIC_DRAW]
		*/
		Buffer(size_t vertexBufferSize, size_t indexBufferSize, GLenum usage = GL_STATIC_DRAW);

		/*
		* Vertex attribute list getter.
		[returns]
		* @ : Vertex attribute list.
		*/
		std::vector<Attribute> getAttributes() const { return mAttributes; }

		/*
		* Add new attribute.
		[params]
		* attr : Attribute to add.
		*/
		void setAttribute(Attribute attr) { mAttributes.push_back(attr); }
		/*
		* Set vertex buffer data.
		[params]
		* data : Vertex buffer data.
		*/
		template<typename T>
		void setVertexBufferData(std::vector<T> data) const {
			this->bind();
			glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], mUsage);
			this->unbind();
		}
		/*
		* Rewrite vertex buffer data.
		[params]
		* data : New buffer data.
		* offset : Offset of new data.
		*/
		template<typename T>
		void setVertexBufferData(std::vector<T> data, size_t offset) const {
			this->bind();
			glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(T) * data.size(), &data[0]);
			this->unbind();
		}
		/*
		* Set index buffer data.
		[params]
		* data : Index buffer data.
		*/
		template<typename T>
		void setIndexBufferData(std::vector<T> data) const {
			this->bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], mUsage);
			this->unbind();
		}
		/*
		* Rewrite index buffer data.
		[params]
		* data :  New index buffer data.
		* offset : Offset of new data.
		*/
		template<typename T>
		void setIndexBufferData(std::vector<T> data, size_t offset) const {
			this->bind();
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(T) * data.size(), &data[0]);
			this->unbind();
		}
		/*
		* Set vertex and index buffer data.
		[params]
		* vertexBufferData : Vertex buffer data.
		* indexBufferData : Index buffer data.
		*/
		template<typename S, typename T>
		void setBufferDatas(std::vector<S> vertexBufferData, std::vector<T> indexBufferData) const {
			this->bind();
			glBufferData(GL_ARRAY_BUFFER, sizeof(S) * vertexBufferData.size(), &vertexBufferData[0], mUsage);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * indexBufferData.size(), &indexBufferData[0], mUsage);
			this->unbind();
		}
		/*
		* Rewrite vertex and index buffer data.
		[params]
		* vertexBufferData : New vertex buffer data.
		* indexBufferData : New index buffer data.
		* vertexDataOffset : Offset of new vertex data.
		* indexDataOffset : Offset of new index data.
		*/
		template<typename S, typename T>
		void setBufferDatas(std::vector<S> vertexBufferData, std::vector<T> indexBufferData, size_t vertexDataOffset, size_t indexDataOffset) const {
			this->bind();
			glBufferSubData(GL_ARRAY_BUFFER, vertexDataOffset, sizeof(S) * vertexBufferData.size(), &vertexBufferData[0]);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexDataOffset, sizeof(T) * indexBufferData.size(), &indexBufferData[0]);
			this->unbind();
		}

		/*
		* Bind all buffers.
		*/
		void bind() const;
		/*
		* Unbind all buffers.
		*/
		void unbind() const;

		operator std::vector<Attribute>() const { return mAttributes; }
	};
}

std::ostream& operator<<(std::ostream& stream, const GeoFrame::Attribute& attribute);
std::ostream& operator<<(std::ostream& stream, const GeoFrame::Buffer& buffer);
