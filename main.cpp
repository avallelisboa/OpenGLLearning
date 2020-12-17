#define GLEW_STATIC

#ifdef _DEBUG
    #include <iostream>
    #define LOG(X) std::cout << X << std::endl
#else
    #define LOG(X)
#endif

#include <malloc.h>
#include <glew.h>
#include <glfw3.h>

#include "Shaders/Shaders.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray.h"

#ifdef _DEBUG
#define CHECKERROR() CheckError()
#define CLEARERROR() ClearError()

void ClearError() {
    while (glGetError() != GL_NO_ERROR);
}
void CheckError() {
    while (GLenum error = glGetError()) {
        LOG("Error: " << error);
    }
}
#else
    #define CHECKERROR()
    #define CLEARERROR()
#endif

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        LOG("Error:" << glewGetErrorString(err));
    }

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer((const void*)positions, sizeof(float) * 4 * 2);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shaders shader("./Shaders/src/vertex.shader", "./Shaders/src/fragment.shader");
    unsigned int shaderId = shader.GetShader();

    CLEARERROR();
    glUseProgram(shaderId);
    CHECKERROR();

    CLEARERROR();
    int uniformLocation = glGetUniformLocation(shaderId, "u_Color");
    CHECKERROR();

    float red, green, blue, redincrement, greenincrement, blueincrement;
    red = 0.0f;
    blue = 1.0f;
    green = 0.5f;
    redincrement = +0.5f;
    greenincrement = +0.5f;
    blueincrement = -0.5f;

    CLEARERROR();
    glUniform4f(uniformLocation, 0.2f, 0.3f, 0.8f, 1.0f);
    CHECKERROR();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (red > 1.0f) redincrement = -0.002f;
        if (red < 0.0f) redincrement = 0.002f;

        if (green > 1.0f) greenincrement = -0.001f;
        if (green < 0.0f) greenincrement = 0.001f;

        if (blue > 1.0f) blueincrement = -0.003f;
        if (blue < 0.0f) blueincrement = 0.003f;

        red += redincrement;
        green += greenincrement;
        blue += blueincrement;

        LOG(red << ", " << green << ", " << blue);

        glUseProgram(shaderId);
        glUniform4f(uniformLocation, red, green, blue, 1.0f);
        vertexArray.Bind();
        indexBuffer.Bind();

        CLEARERROR();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        CHECKERROR();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}