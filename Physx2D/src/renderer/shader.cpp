#include "pch.h"
#include "shader.h"
#include "../core/Log.h"

namespace Physx2D {

	std::string get_file_content(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);

		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw("ERROR : Invalid file path %s\n", filename); //TODO
	}

	unsigned int Shader::compile_shader(const char* source, GLenum type) {
		unsigned int  id;
		int success;
		char infoLog[512];

		id = glCreateShader(type);
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (not success) {
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			LOG_ERROR("ERROR: %s Shader did not compiled successfully\n LOG : %s\n", (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), infoLog);
		}
		return id;
	}

	Shader::Shader() : m_ID(0) {
	}

	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		unsigned int vertShader, fragShader;

		std::string vertString = get_file_content(vertexPath);
		std::string fragString = get_file_content(fragmentPath);

		const char* vertexCode = vertString.c_str();
		const char* fragmentCode = fragString.c_str();

		vertShader = compile_shader(vertexCode, GL_VERTEX_SHADER);
		fragShader = compile_shader(fragmentCode, GL_FRAGMENT_SHADER);

		m_ID = glCreateProgram();
		
		glAttachShader(m_ID, vertShader);
		glAttachShader(m_ID, fragShader);
		glLinkProgram(m_ID);
		{// Link status check
			int success;
			char infoLog[512];

			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (not success) {
				glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
				LOG_ERROR("ERROR : Shader program did not link successfully, paths : vertex_shader : %s , fragment_shader : %s\nLOG:%s\n", vertexPath, fragmentPath, infoLog);
			}
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	void Shader::use() {
		glUseProgram(m_ID);
	}

	void Shader::del() {
		glDeleteProgram(m_ID);
	}

	void Shader::setBool(const char* name, bool value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1i(glGetUniformLocation(m_ID, name), (int)value);
		else
			LOG_WARN("WARNING : location of boolean %s not found\n", name);
	}

	void Shader::setInt(const char* name, int value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1i(glGetUniformLocation(m_ID, name), value);
		else
			LOG_WARN("WARNING : location of integer %s not found\n", name);
	}

	void Shader::setFloat(const char* name, float value) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform1f(glGetUniformLocation(m_ID, name), value);
		else
			LOG_WARN("WARNING : location of float %s not found\n", name);
	}

	void Shader::setVec2(const char* name, vec2 vec) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniform2f(glGetUniformLocation(m_ID, name), vec.x, vec.y);
		else
			LOG_WARN("WARNING : location of vec2 %s not found\n", name);
	}

	void Shader::setMat3(const char* name, mat3 mat) {
		if (glGetUniformLocation(m_ID, name) >= 0)
			glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &mat.value[0][0]);
		else
			LOG_WARN("WARNING : location of mat3 %s not found\n", name);
	}
}