#pragma once
#include <glad/glad.h>

namespace Physx2D {
	std::string get_file_content(const char* filename);
	uint32_t compile_shader(const char* source, GLenum type);
}