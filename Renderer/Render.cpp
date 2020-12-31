#include "Render.h"
#include "../Textures/Texture.h"

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

void Renderer::Clear(){
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shaders& shader){
	va.Bind();
	ib.Bind();

	//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f );

	Texture texture("Textures/src/Obi-Wan.png");
	texture.Bind();

	shader.SetUniform1i("u_Texture", 0);

	CLEARERROR();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	CHECKERROR();
}