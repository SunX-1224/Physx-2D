#pragma once

#include <glad/glad.h>
#include "../math/math.h"

namespace Physx2D {

	

	class PHYSX2D_API Shader {
	public:
		uint32_t m_ID;

		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);

		inline void use();
		inline void del();
		inline void setBool(const char*, bool);
		inline void setInt(const char*, int);
		inline void setFloat(const char*, float);
		inline void setVec2(const char*, vec2);
		inline void setMat3(const char*, mat3);
	};
}