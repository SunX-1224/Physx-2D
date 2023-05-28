#pragma once
#include <glad/glad.h>

class PHYSX2D_API Buffer {
	public:
		
		Buffer(GLenum type);
		inline void setBufferData(const void* data, size_t size);
		inline void bind();
		inline void bindBase(uint32_t index);
		inline void del();

		inline void unbind();

	private:
		GLenum m_type;
		uint32_t m_ID;
};

