#include "Shaders.h"

void Shaders::Load(const char* vertexShaderPath, const char* fragmentShaderPath){
	FileTools vertex;
	FileTools fragment;
	
	m_vertexShaderSource = vertex.LoadFile(vertexShaderPath);
	m_fragmentShaderSource = fragment.LoadFile(fragmentShaderPath);

    if (!(m_vertexShaderSource || m_fragmentShaderSource)) {
#ifdef _DEBUG    
        LOG("No se ha podido cargar los archivos que contienen al shader");    
#endif
        return;
    }

    CreateShader();
}

unsigned int Shaders::CompileShader(unsigned int type, const char* source){
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(int) * length);
        glGetShaderInfoLog(id, length, &length, message);

        LOG("Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader");
        LOG(message);

        glDeleteShader(id);

        return 0;
    }

    return id;
}

void Shaders::CreateShader(){
    //Defines a shader and gets the shader Id
    m_Shader = glCreateProgram();

    //Compiles the shaders
    m_VertexShader = CompileShader(GL_VERTEX_SHADER, m_vertexShaderSource);
    m_FragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_fragmentShaderSource);
}

Shaders::Shaders(const char* vertexShaderPath, const char* fragmentShaderPath):m_RendererID(0){
    Load(vertexShaderPath, fragmentShaderPath);
}

Shaders::~Shaders(){
	free((void*)m_vertexShaderSource);
	free((void*)m_fragmentShaderSource);

    Unbind();
    glDeleteProgram(m_Shader);
}

void Shaders::Bind() const{
    //Attaches vertex shader
    glAttachShader(m_Shader, m_VertexShader);
    //Attaches fragment shader
    glAttachShader(m_Shader, m_FragmentShader);
    //Links Shader
    glLinkProgram(m_Shader);
    //Validates the shader is correct
    glValidateProgram(m_Shader);
    //Deletes the intermediate shader files
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shaders::Unbind() const{
    glUseProgram(0);
}

int Shaders::GetUniformLocation(const char* name) const{
    int location = glGetUniformLocation(m_Shader, name);
    if (location == -1) {
        LOG("Error: The uniform" << name << "does not exist!");
        return location;
    }
}

void Shaders::SetUniform4f(const char* name, float v0, float v1, float f2, float f3){
    glUniform4f(GetUniformLocation(name), v0, v1, f2, f3);
}
