#pragma once
/*
	Buffer is a general class for any type of buffer objects in the program. This is a wrapper class
	for opengl's buffer objects. 
	Functionalities : 
		> setBufferData
		> bind
		> bindBase at index
		> del
*/

#include <glad/glad.h>

namespace Physx2D {
	class PHYSX2D_API Buffer {
	public:

		Buffer(GLenum type);
		~Buffer();

		inline void setBufferData(const void* data, size_t size, GLenum useMode = GL_STATIC_DRAW);
		inline void bind();
		inline void bindBase(uint32_t index);

		inline void unbind();

	private:
		GLenum m_type;
		uint32_t m_ID;
	};
}