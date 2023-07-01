#include "pch.h"
#include "Buffer.h"


namespace Physx2D {
	Buffer::Buffer(GLenum type) {
		glGenBuffers(1, &m_ID);
		this->m_type = type;
	}

	inline void Buffer::setBufferData(const void* data, size_t size, GLenum useMode) {
		glBindBuffer(m_type, m_ID);
		glBufferData(m_type, size, data, useMode);
	}

	inline void Buffer::bind() {
		glBindBuffer(m_type, m_ID);
	}

	inline void Buffer::bindBase(uint32_t index) {
		glBindBufferBase(m_type, index, m_ID);
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &m_ID);
	}

	inline void Buffer::unbind() {
		glBindBuffer(m_type, 0);
	}
}