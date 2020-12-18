#pragma once
#ifdef _DEBUG
	#include <iostream>
	#define LOG(X) std::cout << X << std::endl
#else
	#define LOG(X)
#endif
#include <glew.h>

#include "../VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shaders/Shaders.h"


#ifdef _DEBUG
#define CHECKERROR() CheckError()
#define CLEARERROR() ClearError()

void GlClearError();
bool GlLogCall();
#else
#define CHECKERROR()
#define CLEARERROR()
#endif


class Renderer {
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shaders& shader, float r, float g, float b) const;
};
