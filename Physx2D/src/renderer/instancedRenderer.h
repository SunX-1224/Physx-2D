#pragma once
#include "../core/core.h"
#include "renderer2D.h"

namespace Physx2D {
	class PHYSX2D_API InstancedRenderer : public Renderer2D {
	public:
		uint32_t m_count;

		InstancedRenderer();
		InstancedRenderer(
			std::vector<vec2> vertices,
			std::vector<uint32_t> indices,
			GLenum mode = GL_TRIANGLES
		);
		InstancedRenderer(
			std::vector<vec2> vertices,
			GLenum mode = GL_TRIANGLES
		);

		void InstanceLayout(
			uint32_t location,
			uint32_t count, 
			GLenum type,
			GLsizei stride,
			uint32_t offset,
			uint32_t divisor = 1
		);

		void InstanceData(void* data, uint32_t count, size_t size_i);
		void Draw(Shader* shader);
		void del();

	protected:
		uint32_t m_ivbo;
	};
}