#pragma once

#include "texture.h"
#include "vao.h"
#include "../utils/defaults.h"

namespace Physx2D {

	class PHYSX2D_API FrameBuffer {
	public:
		VAO m_vao;
		FrameBuffer(
			int width,
			int height,
			uint32_t defaultSlot = 0,
			GLenum _dtype = GL_UNSIGNED_BYTE
		);
		void del();

		inline void Clear(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		inline void ActivateAsTexture(int slot = -1);
		inline void Bind();
		static inline void Unbind();
		void Draw(Shader& shader);

	private:
		uint32_t m_ID;
		uint32_t m_rbo = NULL;
		uint32_t m_slot = NULL;
		Texture* m_texture;
		void attachVertexArray();
		void attachRenderBuffer();
	};
}