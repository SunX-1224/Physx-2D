#include "pch.h"
#include "renderer2D.h"

namespace Physx2D {
	Renderer2D::Renderer2D() {
		m_vbo = 0;
		m_ebo = 0;
		p_count = 0;
		m_renderMode = 0;
	}

	Renderer2D::Renderer2D(std::vector<float> vertices, std::vector<uint32_t> indices, GLenum mode) :
		m_renderMode(mode), p_count(indices.size()), arrayMode(false)
	{
		m_vao.bind();

		glGenBuffers(1, &m_vbo);
		BufferData(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(vertices[0]));

		glGenBuffers(1, &m_ebo);
		BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(indices[0]));
	}

	Renderer2D::Renderer2D(std::vector<float> vertices, uint32_t numPoints, GLenum mode) 
		:m_renderMode(mode), arrayMode(true), p_count(numPoints), m_ebo(0)
	{
		glGenBuffers(1, &m_vbo);
		BufferData(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(vertices[0]));
	}

	inline void Renderer2D::BufferData(GLenum type, void* data, size_t size, GLenum usemode) {
		m_vao.bind();
		glBindBuffer(type, type==GL_ELEMENT_ARRAY_BUFFER?m_ebo:m_vbo); //********FLAG**********
		glBufferData(type, size, data, usemode);
		m_vao.unbind();
		glBindBuffer(type, 0);
	}

	void Renderer2D::VertexDataLayout(uint32_t location, uint32_t count, GLenum type, GLsizei stride, uint32_t offset) {
		m_vao.bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_vao.layout(location, count, type, stride, offset);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vao.unbind();
	}

	void Renderer2D::Draw(Shader* shader) {
		shader->use();
		m_vao.bind();
		if(arrayMode) 
			glDrawArrays(m_renderMode, 0, p_count);
		else
			glDrawElements(m_renderMode, p_count, GL_UNSIGNED_INT, 0);
		m_vao.unbind();
	}

	void Renderer2D::del(){
		m_vao.del();
		glDeleteBuffers(1, &m_vbo);
		if(m_ebo)
			glDeleteBuffers(1, &m_ebo);
	}
}