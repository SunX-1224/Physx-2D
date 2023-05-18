#include "vao.h"

namespace Physx2D {
	VAO::VAO() {
		glGenVertexArrays(1, &m_ID);
	}

	void VAO::layout(GLuint location, GLuint size, GLenum type, GLuint stride, unsigned int offset) {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, size, type, GL_FALSE, stride, (void*)offset);
	}

	void VAO::bind() {
		glBindVertexArray(m_ID);
	}

	void VAO::unbind() {
		glBindVertexArray(0);
	}

	void VAO::del() {
		glDeleteVertexArrays(1, &m_ID);
	}
}