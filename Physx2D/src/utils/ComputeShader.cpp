#include "pch.h"
#include "ComputeShader.h"
#include <glad/glad.h>

namespace Physx2D {
	ComputeShader::ComputeShader(const char* compute_shader, bool is_path) {
		uint32_t shader;

		if (is_path) {
			std::string c_ = get_file_content(compute_shader);
			const char* src = c_.c_str();
			shader = compile_shader(src, GL_COMPUTE_SHADER);
		}
		else {
			shader = compile_shader(compute_shader, GL_COMPUTE_SHADER);
		}

		m_ID = glCreateProgram();

		glAttachShader(m_ID, shader);
		glLinkProgram(m_ID);
		{// Link status check
			int success;
			char infoLog[512];

			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
				LOG_ERROR("ERROR : Compute Shader program did not link successfully, path : %s\nLOG:%s\n", compute_shader, infoLog);
			}
		}
		glDeleteShader(shader);

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

	inline void ComputeShader::setInt(const char* u_name, int value) {
		if (glGetUniformLocation(m_ID, u_name) >= 0)
			glUniform1i(glGetUniformLocation(m_ID, u_name), value);
		else
			LOG_WARN("WARNING : location of integer %s not found\n", u_name);
	}

	inline void ComputeShader::setFloat(const char* u_name, float value) {
		if (glGetUniformLocation(m_ID, u_name) >= 0)
			glUniform1f(glGetUniformLocation(m_ID, u_name), value);
		else
			LOG_WARN("WARNING : location of float %s not found\n", u_name);
	}

	inline tvec3<int> ComputeShader::getWorkGrpCount()
	{
		tvec3<int> tmp;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &tmp.x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &tmp.y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &tmp.z);

		return tmp;
	}

	inline tvec3<int> ComputeShader::getWorkGrpSize()
	{
		tvec3<int> tmp;
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