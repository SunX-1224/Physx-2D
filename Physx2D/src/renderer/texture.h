#pragma once

#include "shader.h"
#include<stb/stb_image.h>

namespace Physx2D {

	class PHYSX2D_API Texture {
	public:

		const char* m_type;
		unsigned int m_slot;
		int m_width, m_height;

		Texture(
			const char* path,
			const char* type,
			unsigned int slot,
			int _width = 800,
			int _height = 800
		);

		void texUnit(Shader& shader, const char* uniform);
		void bind(int slot = -1);
		static void unbind();
		void del();
		void set_property(GLenum target, GLenum pname, GLenum parameter);
		uint32_t ID();
	private:
		GLuint m_ID;

	};
}