#include "pch.h"
#include "vao.h"

namespace Physx2D {
	VAO::VAO() {
		glGenVertexArrays(1, &m_ID);
	}

	VAO::~VAO() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void VAO::layout(GLuint location, GLuint count, GLenum type, GLuint stride, unsigned int offset) {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, count, type, GL_FALSE, stride, (void*)offset);
	}

	void VAO::bind() {
		glBindVertexArray(m_ID);
	}

	void VAO::unbind() {
		glBindVertexArray(0);
	}

}