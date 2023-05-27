#include "pch.h"
#include "ComputeShader.h"
#include <glad/glad.h>

namespace Physx2D {
	ComputeShader::ComputeShader(const char* path) {

		std::string src_str = get_file_content(path);

		const char* src = src_str.c_str();

		uint32_t shader = compile_shader(src, GL_COMPUTE_SHADER);

		m_ID = glCreateProgram();

		glAttachShader(m_ID, shader);
		glLinkProgram(m_ID);
		{// Link status check
			int success;
			char infoLog[512];

			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (not success) {
				glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
				LOG_ERROR("ERROR : Compute Shader program did not link successfully, path : %s\nLOG:%s\n", path, infoLog);
			}
		}
		glDeleteShader(shader); // FLAG: If any errors, remove this line

	}

ComputeShader::~ComputeShader() {
	glDeleteProgram(m_ID);
}

	inline void ComputeShader::dispatch(uint32_t x, uint32_t y, uint32_t z) {
		glUseProgram(m_ID);
		glDispatchCompute(x, y, z);
	}

	inline void ComputeShader::waitUntilFinish(GLbitfield barrier) {
		glMemoryBarrier(barrier);
	}

	inline void ComputeShader::use() {
		glUseProgram(m_ID);
	}

	inline vec3<int> ComputeShader::getWorkGrpCount()
	{
		vec3<int> tmp;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &tmp.x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &tmp.y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &tmp.z);

		return tmp;
	}

	inline vec3<int> ComputeShader::getWorkGrpSize()
	{
		vec3<int> tmp;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &tmp.x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &tmp.y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &tmp.z);

		return tmp;
	}

	inline int ComputeShader::maxLocalWorkGrpInv()
	{
		GLint tmp;
		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &tmp);
		return tmp;
	}
}