#pragma once
#ifdef _DEBUG
	#include <iostream>
	#define LOG(X) std::cout << X << std::endl
#else
	#define LOG(X)
#endif
#include <glew.h>

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Draw();
};
