#include "pch.h"
#include "framebuffer.h"
#include "../core/Log.h"

namespace Physx2D {
	FrameBuffer::FrameBuffer(int width, int height, uint32_t defaultSlot, GLenum _dtype) : m_vao(new VAO) {

		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		m_texture = new Texture(NULL, "frame", defaultSlot, width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->ID(), 0);
		attachRenderBuffer();
		attachVertexArray();
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);
		glDeleteRenderbuffers(1, &m_rbo);
		delete m_vao;
		delete m_texture;
	}

	void FrameBuffer::attachRenderBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_texture->m_width, m_texture->m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Error while attaching framebuffer%s", "\n");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::attachVertexArray() {

		unsigned int  rectVBO;

		m_vao->bind();
		glGenBuffers(1, &rectVBO);

		glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FRAME_QUAD), &FRAME_QUAD, GL_STATIC_DRAW);

		m_vao->layout(0, 2, GL_FLOAT, 4 * sizeof(float), 0);
		m_vao->layout(1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
		m_vao->unbind();
	}

	inline void FrameBuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	inline void FrameBuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline void FrameBuffer::Clear(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void FrameBuffer::ActivateAsTexture(int slot) {
		m_texture->bind(slot);
	}

	inline void FrameBuffer::Draw(Shader& shader) {
		shader.use();
		m_vao->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_vao->unbind();
		Texture::unbind();
	}
}