#pragma once

#define GLEW_STATIC

#ifdef _DEBUG
#include <iostream>
#define LOG(X) std::cout << X << std::endl
#else
#define LOG(X)
#endif

#include <stdio.h>
#include <malloc.h>
#include <glew.h>
#include <glfw3.h>
#include "../FileTools.h"

#include "glm/glm.hpp"

class Shaders
{
	private:
		unsigned int m_RendererID;

		const char* m_vertexShaderSource;
		const char* m_fragmentShaderSource;

		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_Shader;

		bool m_IsBound;

		void Load(const char* vertexShaderPath, const char* fragmentShaderPath);
		unsigned int CompileShader(unsigned int type, const char* source);
		void CreateShader();
	public:
		inline unsigned int GetShader() const { return m_Shader; };

		Shaders(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shaders();

		void Bind();
		void Unbind();

		int GetUniformLocation(const char* name) const;
		inline bool IsBound() const { return m_IsBound; }

		void SetUniform1i(const char* name, int value);
		void SetUniform1f(const char* name, float value);
		void SetUniform4f(const char* name, float v0, float v1, float f2, float f3);

		void SetUniformMat4f(const char* name, const glm::mat4& matrix);
};

