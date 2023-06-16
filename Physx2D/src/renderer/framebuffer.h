#pragma once

/*
	FrameBuffer object can be used to draw any content on them instead of screen and post-process it.
	Functionalities : 
		> Construction : requires width, height of frame and defaultSlot (0->16) and finally 
			datatype for single element/pixel of framebuffer
		> del will clear all buffers and delete the framebuffer
		> Clear will clear the color in framebuffer
		> ActivateAsTexture will activate framebuffer's content as a texture in the defaultSlot or any slot(0->16) if provided
		> Bind will bind the framebuffer as target buffer for drawing
		> Unbind will unbind framebuffer and binds the default frame i.e. window
		> Draw will draw framebuffer on the screen with the shader specified in parameter

		Currently framebuffer is drawn on whole screen, so there is not much control on where to draw it, but it will be fixed soon.
*/

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