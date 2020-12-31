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

#include "imgui.h"
#include <imgui_impl_glfw.cpp>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include "Buffers/VertexBuffer.h"
#include "Buffers/VertexBufferLayout.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray.h"
#include "Shaders/Shaders.h"
#include "Renderer/Render.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
       // Problem: glewInit failed, something is seriously wrong.
        LOG("Error:" << glewGetErrorString(err));
    }

    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f,
        200.0f, 100.0f, 1.0f, 0.0f,
        200.0f, 200.0f, 1.0f, 1.0f,
        100.0f, 200.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    //Enables blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray vertexArray;
    VertexBuffer vertexBuffer((const void*)positions, sizeof(float) * 4 * 4);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shaders shader("./Shaders/src/vertex.shader", "./Shaders/src/fragment.shader");
    shader.Bind();

    glm::vec3 translation(200, 200, 0);

    glm::mat4 projectionMat = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 mvp = projectionMat * viewMat * modelMat;

    shader.SetUniformMat4f("u_MVP", mvp);

    Renderer renderer;
    renderer.Draw(vertexArray, indexBuffer, shader);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


   /* float red, green, blue, redincrement, greenincrement, blueincrement;
    red = 0.0f;
    blue = 1.0f;
    green = 0.5f;
    redincrement = 0.0f;
    greenincrement = 0.0f;
    blueincrement = 0.0f;*/

    //shader.SetUniform4f("u_Color", red, green, blue, 1.0f);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::SameLine();


            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        projectionMat = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        modelMat = glm::translate(glm::mat4(1.0f), translation);
        mvp = projectionMat * viewMat * modelMat;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        
        renderer.Draw(vertexArray, indexBuffer, shader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /*
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
        */
        //shader.SetUniform4f("u_Color", red, green, blue, 1.0f);
        //shader.SetUniformMat4f("u_MVP", projectionMat);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}