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

		inline void texUnit(Shader* shader, const char* uniform);
		inline void bind(int slot = -1);
		static inline void unbind();
		inline void del();
		inline void set_property(GLenum target, GLenum pname, GLenum parameter);
		uint32_t ID();
	private:
		GLuint m_ID;

	};
}