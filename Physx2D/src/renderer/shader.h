#pragma once

/*
	Shader object currently manages the vertex and fragment shaders only. Shaders can 
	written in any file format but the language must be glsl.
	Functionalities : 
		> use : use the current shader
		> del : delete the shader program
		> set**** : set the **** value of uniform variable
*/

#include <glad/glad.h>
#include "../math/math.h"

namespace Physx2D {

	class PHYSX2D_API Shader {
	public:
		uint32_t m_ID;

		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		inline void use();
		inline void setBool(const char*, bool);
		inline void setInt(const char*, int);
		inline void setFloat(const char*, float);
		inline void setVec2(const char*, vec2);
		inline void setMat3(const char*, mat3);
	};
}