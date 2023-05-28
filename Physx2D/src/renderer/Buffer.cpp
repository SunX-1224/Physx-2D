#include "pch.h"
#include "Buffer.h"

Buffer::Buffer(GLenum type) {
	glGenBuffers(1, &m_ID);
	this->m_type = type;
}

inline void Buffer::setBufferData(const void* data, size_t size) {
	glBindBuffer(m_type, m_ID);
	glBufferData(m_type, size, data, GL_STATIC_DRAW);
	glBindBuffer(m_type, 0);
}

inline void Buffer::bind() {
	glBindBuffer(m_type, m_ID);
}

inline void Buffer::bindBase(uint32_t index) {
	glBindBufferBase(m_type, index, m_ID);
}

inline void Buffer::del() {
	glDeleteBuffers(1, &m_ID);
}

inline void Buffer::unbind() {
	glBindBuffer(m_type, 0);
}
