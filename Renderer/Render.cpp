#include "Render.h"

#ifdef _DEBUG
#define CHECKERROR() GlLogCall()
#define CLEARERROR() GlClearError()

void GlClearError(){
	while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall()
{
	while (GLenum error = glGetError()) {
		LOG("Error: " << error);
	}
	return true;
}
#else
#define CHECKERROR()
#define CLEARERROR()
#endif

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shaders& shader, float r, float g, float b) const
{
	CLEARERROR();
	va.Bind();
	CHECKERROR();
	CLEARERROR();
	ib.Bind();
	CHECKERROR();
	CLEARERROR();
	shader.Bind();
	CHECKERROR();
	CLEARERROR();
	shader.SetUniform4f("u_Color", r, g, b, 1.0f);
	CHECKERROR();
	CLEARERROR();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	CHECKERROR();
}