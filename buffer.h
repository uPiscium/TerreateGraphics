#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include "core.h"
#include "exception.h"

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

	template<typename T>
	class VertexBuffer {
	private:
		unsigned mID = 0;
		BufferType mBufferType = BufferType::ARRAY_BUFFER;
		BufferUsage mUsage = BufferUsage::STATIC_DRAW;
		size_t mBufferComponents = 0;
		size_t mComponentSize = sizeof(T);
		GLType mDataType = TYPE2GL(typeid(T));
		std::vector<Attribute> mAttributes = {};

	public:
		/*
		* Vertex buffer or index buffer creation class.
		[params]
		* type : Type of this buffer.
		* usage : Usage of this buffer. {Default : BufferUsage::STATIC_DRAW}
		[notes]
		* STATIC_~~~ is used for static data. It shouldn't be changed frequentry.
		* DYNAMIC_~~~ is used for dynamic data. It can be changed frequentry.
		* ARRAY_BUFFER can be used as position, color, tex pos, or etc... buffer.
		* ELEMENT_BUFFER can be used as index buffer.
		*/
		VertexBuffer(BufferType type, BufferUsage usage = BufferUsage::STATIC_DRAW)
			: mBufferType(type), mUsage(usage)
		{
			glGenBuffers(1, &mID);
		}
		/*
		* Vertex buffer creation class.
		[params]
		* type : Type of this buffer.
		* data : Buffer data.
		* usage : Usage of this buffer. {Default : BufferUsage::STATIC_DRAW}
		[notes]
		* STATIC_~~~ is used for static data. It shouldn't be changed frequentry.
		* DYNAMIC_~~~ is used for dynamic data. It can be changed frequentry.
		* ARRAY_BUFFER can be used as position, color, tex pos, or etc... buffer.
		* ELEMENT_BUFFER can be used as index buffer.
		*/
		VertexBuffer(BufferType type, const std::vector<T>& data, BufferUsage usage = BufferUsage::STATIC_DRAW)
			: mBufferType(type), mUsage(usage)
		{
			glGenBuffers(1, &mID);
			this->SetBufferData(data);
		}

		/*
		* Get vertex attribute list.
		[returns]
		* std::vector<Attribute> : Vertex attribute list.
		*/
		std::vector<Attribute> GetAttributes() const { return mAttributes; }
		/*
		* Get the size of buffer count in bytes.
		[returns]
		* size_t : Buffer size.(bytes)
		*/
		size_t GetSize() const { return mBufferComponents * mComponentSize; }
		/*
		* Get the number of components of buffer.
		[returns]
		* size_t : Number of components of buffer.
		*/
		size_t GetNumComponents() const { return mBufferComponents; }
		/*
		* Get buffer component type.
		[returns]
		* GLType: Buffer component type.
		*/
		GLType GetComponentType() const { return mDataType; }
		/*
		* Get buffer type.
		[returns]
		* BufferType : Buffer type.
		*/
		BufferType GetBufferType() const { return mBufferType; }

		/*
		* Add new attribute.
		[params]
		* attr : Attribute to add.
		*/
		void SetAttribute(Attribute attr) { mAttributes.push_back(attr); }
		/*
		* Set buffer data.
		[params]
		* data : Buffer data.
		*/
		void SetBufferData(const std::vector<T>& data) {
			mBufferComponents = data.size();
			glBindBuffer((GLenum)mBufferType, mID);
			glBufferData((GLenum)mBufferType, this->GetSize(), &data[0], (GLenum)mUsage);
			glBindBuffer((GLenum)mBufferType, 0);
		}
		
		/*
		* Update vertex buffer data.
		[params]
		* data : New buffer data.
		* offset : Offset of new data. {Default : 0}
		[WARNING]
		* Call non offset version before calling this.
		* The template type <T> must be the same as written data type.
		* Data size must be less than written data size.
		*/
		void UpdateBufferData(const std::vector<T>& data, size_t offset = 0) {
			glBindBuffer((GLenum)mBufferType, mID);
			glBufferSubData((GLenum)mBufferType, offset * mComponentSize, data.size() * mComponentSize, &data[0]);
			glBindBuffer((GLenum)mBufferType, 0);
		}
		/*
		* Bind all buffers.
		*/
		void Bind() const { glBindBuffer((GLenum)mBufferType, mID); }
		/*
		* Unbind all buffers.
		*/
		void Unbind() const { glBindBuffer((GLenum)mBufferType, 0); }
	};

	class VertexArray {
	private:
		unsigned mID;
		size_t mIndices = 0;
		GLType mIndexType = GLType::UNSIGNED_INT;

	private:
		std::pair<size_t, std::vector<size_t>> GetAttributeDatas(const std::vector<Attribute>& attrs);

	public:
		/*
		* Vertex array creation class.
		*/
		VertexArray();

		/*
		* Register vertex buffer to vertex array.
		[params]
		* buffer : Buffer to register.
		*/
		template<typename T>
		void Register(const VertexBuffer<T>& buffer) {
			const std::vector<Attribute>& attrs = buffer.GetAttributes();

			if (buffer.GetBufferType() == BufferType::ELEMENT_BUFFER) {
				mIndices = buffer.GetNumComponents();
				mIndexType = buffer.GetComponentType();
			}
			else { ; }

			if (attrs.size() != 0) {
				auto data = this->GetAttributeDatas(attrs);
				const size_t& strideSize = data.first;
				const std::vector<size_t>& offsets = data.second;

				glBindVertexArray(mID);
				buffer.Bind();
				for (unsigned i = 0; i < attrs.size(); i++) {
					const Attribute& attr = attrs[i];
					size_t stride, offset;
					stride = attr.mStride == -1 ? strideSize : attr.mStride;
					offset = attr.mOffset == -1 ? offsets[i] : attr.mOffset;

					if (attr.mDivisor != -1) {
						glVertexAttribDivisor(i, attr.mDivisor);
					}
					else { ; }

					glEnableVertexAttribArray(i);
					glVertexAttribPointer(
						i, attr.mComponents, (GLenum)attr.mType, GL_FALSE,
						stride, (void*)offset
					);
				}

				glBindVertexArray(0);
				buffer.Unbind();
			}
			else {
				glBindVertexArray(mID);
				buffer.Bind();
				glBindVertexArray(0);
				buffer.Unbind();
			}
		}

		/*
		* Draw registered buffers.
		[params]
		* mode : Draw mode of OpenGL. {Default : DrawMode::TRIANGLES}
		[notes]
		* If you want to draw the same object many times, "DrawInstances()" method is more suited.
		*/
		void Draw(DrawMode mode = DrawMode::TRIANGLES);
		/*
		* Draw registered buffers.
		[params]
		* numOfInstances : Number of instances you want to draw.
		* mode : Draw mode of OpenGL. {Default : DrawMode::TRIANGLES}
		*/
		void DrawInstances(size_t numOfInstances, DrawMode mode = DrawMode::TRIANGLES);
	};
}

std::ostream& operator<<(std::ostream& stream, const GeoFrame::Attribute& attribute);
