#pragma once
#include "vao.h"
#include "shader.h"

namespace Physx2D {
	class PHYSX2D_API Renderer2D {
	public:
		GLenum m_renderMode;

		Renderer2D();
		Renderer2D(std::vector<float> vertices, std::vector<uint32_t> indices, GLenum mode = GL_TRIANGLES);
		Renderer2D(std::vector<float> vertices, uint32_t numPoints, GLenum mode = GL_TRIANGLES);

		void VertexData(void* data, uint32_t count, size_t size_i);
		void IndexData(void* data, uint32_t count, size_t size_i);
		void VertexDataLayout(uint32_t location, uint32_t count, GLenum type, GLsizei size_i, uint32_t offset);
		virtual void Draw(Shader* shader);
		virtual void del();

	protected:
		VAO m_vao;
		uint32_t p_count;
		bool arrayMode = true;
		uint32_t m_vbo, m_ebo;
	};
}