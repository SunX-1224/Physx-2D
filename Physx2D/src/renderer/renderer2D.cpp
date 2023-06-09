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
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

		m_vao.unbind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Renderer2D::Renderer2D(std::vector<float> vertices, uint32_t numPoints, GLenum mode) 
		:m_renderMode(mode), arrayMode(true), p_count(numPoints), m_ebo(0)
	{
		m_vao.bind();

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), vertices.data(), GL_STATIC_DRAW);

		m_vao.unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer2D::VertexData(void* data, uint32_t count, size_t size_i) {
		m_vao.bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, size_i * count, data, GL_STATIC_DRAW);
		m_vao.unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer2D::IndexData(void* data, uint32_t count, size_t size_i) {
		p_count = count;
		m_vao.bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_i * count, data, GL_STATIC_DRAW);
		m_vao.unbind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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