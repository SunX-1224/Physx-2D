#include "framebuffer.h"

namespace Physx2D {
	FrameBuffer::FrameBuffer(int width, int height, uint32_t defaultSlot, GLenum _dtype) {

		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		m_texture = new Texture(NULL, "frame", defaultSlot, width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->ID(), 0);
		attachRenderBuffer();
		attachVertexArray();
	}

	void FrameBuffer::del() {
		glDeleteFramebuffers(1, &m_ID);
		glDeleteRenderbuffers(1, &m_rbo);
		m_vao.del();
		m_texture->del();
		delete(m_texture);
	}

	void FrameBuffer::attachRenderBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_texture->m_width, m_texture->m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR while attaching the framebuffer" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::attachVertexArray() {
		float quadVertices[] = {
			//positions    texture_UVs
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,

			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
		};

		unsigned int  rectVBO;

		m_vao.bind();
		glGenBuffers(1, &rectVBO);

		glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

		m_vao.layout(0, 2, GL_FLOAT, 4 * sizeof(float), 0);
		m_vao.layout(1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
		m_vao.unbind();
	}

	void FrameBuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	void FrameBuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Clear(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void FrameBuffer::ActivateAsTexture(int slot) {
		m_texture->bind(slot);
	}

	void FrameBuffer::Draw(Shader& shader) {
		shader.use();
		m_vao.bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_vao.unbind();
		Texture::unbind();
	}
}