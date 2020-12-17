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

class Shaders
{
	private:
		const char* m_vertexShaderSource;
		const char* m_fragmentShaderSource;
		unsigned int m_Shader;

		void Load(const char* vertexShaderPath, const char* fragmentShaderPath);
		unsigned int CompileShader(unsigned int type, const char* source);
		void CreateShader();
	public:
		inline unsigned int GetShader() const { return m_Shader; };

		Shaders(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shaders();
};

