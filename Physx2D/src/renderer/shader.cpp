#include "pch.h"
#include "shader.h"
#include "../core/Log.h"
#include "../utils/utils.h"

namespace Physx2D {

	Shader::Shader() : m_ID(0) {
	}

	Shader::Shader(const char* vertex_shader, const char* fragment_shader, bool is_path) {
		uint32_t vertShader, fragShader;

		if (is_path) {
			std::string v_ = get_file_content(vertex_shader);
			std::string f_ = get_file_content(fragment_shader);

			const char* vertexCode = v_.c_str();
			const char* fragmentCode = f_.c_str();

			vertShader = compile_shader(vertexCode, GL_VERTEX_SHADER);
			fragShader = compile_shader(fragmentCode, GL_FRAGMENT_SHADER);
		}
		else {
			vertShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
			fragShader = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);
		}

		m_ID = glCreateProgram();
		
		glAttachShader(m_ID, vertShader);
		glAttachShader(m_ID, fragShader);
		glLinkProgram(m_ID);
		
		// Link status check
		{
			int success;
			char infoLog[512];

			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
				LOG_ERROR("ERROR : Shader program did not link successfully : \nLOG:%s\n", infoLog);
			}
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	inline void Shader::use() {
		glUseProgram(m_ID);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ID);
	}

	inline void Shader::setBool(const char* name, bool value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1i(glGetUniformLocation(m_ID, name), (int)value);
		else
			LOG_WARN("WARNING : location of boolean %s not found\n", name);
	}

	inline void Shader::setInt(const char* name, int value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1i(glGetUniformLocation(m_ID, name), value);
		else
			LOG_WARN("WARNING : location of integer %s not found\n", name);
	}

	inline void Shader::setFloat(const char* name, float value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1f(glGetUniformLocation(m_ID, name), value);
		else
			LOG_WARN("WARNING : location of float %s not found\n", name);
	}

	inline void Shader::setVec2(const char* name, vec2 vec) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform2f(glGetUniformLocation(m_ID, name), vec.x, vec.y);
		else
			LOG_WARN("WARNING : location of vec2 %s not found\n", name);
	}

	inline void Shader::setMat3(const char* name, mat3 mat) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &mat.value[0][0]);
		else
			LOG_WARN("WARNING : location of mat3 %s not found\n", name);
	}
}