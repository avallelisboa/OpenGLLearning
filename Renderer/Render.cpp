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

	glm::mat4 projectionMat = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
	glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

	glm::mat4 mvp = projectionMat * viewMat * modelMat;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f );

	Texture texture("Textures/src/Obi-Wan.png");
	texture.Bind();

	shader.SetUniform1i("u_Texture", 0);

	CLEARERROR();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	CHECKERROR();
}