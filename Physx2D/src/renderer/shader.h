#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include "../core/core.h"
#include "../math/math.h"

namespace Physx2D {

	std::string get_file_content(const char*);

	class PHYSX2D_API Shader {
	public:
		uint32_t m_ID;

		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);

		void use();
		void del();
		void setBool(const char*, bool);
		void setInt(const char*, int);
		void setFloat(const char*, float);
		void setVec2(const char*, vec2);
		void setMat3(const char*, mat3);
		static unsigned int compile_shader(const char*, GLenum);
	};
}