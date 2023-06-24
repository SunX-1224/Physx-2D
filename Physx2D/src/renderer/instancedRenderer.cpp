#include "pch.h"
#include "instancedRenderer.h"

namespace Physx2D {

	InstancedRenderer::InstancedRenderer() {
		m_count = 0;
		m_ivbo = 0;
	}

	InstancedRenderer::InstancedRenderer(std::vector<float> vertices, std::vector<uint32_t> indices, GLenum mode) :
		Renderer2D(vertices, indices, mode)
	{
		m_count = 1;
		glGenBuffers(1, &m_ivbo);
	}

	InstancedRenderer::InstancedRenderer(std::vector<float> vertices, uint32_t numPoints, GLenum mode) :
		Renderer2D(vertices, numPoints, mode)
	{
		m_count = 1;
		glGenBuffers(1, &m_ivbo);
	}

	void InstancedRenderer::InstanceLayout(uint32_t location,uint32_t count, GLenum type, GLsizei stride, uint32_t offset, uint32_t divisor) {
		m_vao.bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_ivbo);

		m_vao.layout(location, count, type, stride, offset);
		glVertexAttribDivisor(location, divisor);

		m_vao.unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InstancedRenderer::InstanceData(void* data, uint32_t count, size_t size_i) {
		m_count = count;
		m_vao.bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_ivbo);
		glBufferData(GL_ARRAY_BUFFER, size_i * count, data, GL_DYNAMIC_DRAW);
		m_vao.unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InstancedRenderer::Draw(Shader* shader) {
		shader->use();
		m_vao.bind();
		if (arrayMode)
			glDrawArraysInstanced(m_renderMode, 0, p_count, m_count);
		else
			glDrawElementsInstanced(m_renderMode, p_count, GL_UNSIGNED_INT, 0, m_count);
		m_vao.unbind();
	}

	InstancedRenderer::~InstancedRenderer(){
		glDeleteBuffers(1, &m_ivbo);
		m_vao.del();
		glDeleteBuffers(1, &m_vbo);
		if(m_ebo)
			glDeleteBuffers(1, &m_ebo);
	}
}