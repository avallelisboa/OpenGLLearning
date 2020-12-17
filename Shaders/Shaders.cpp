#include "Shaders.h"

void Shaders::Load(const char* vertexShaderPath, const char* fragmentShaderPath)
{
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

unsigned int Shaders::CompileShader(unsigned int type, const char* source)
{
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

void Shaders::CreateShader()
{
    //Defines a shader and gets the shader Id
    unsigned int program = glCreateProgram();

    //Compiles the shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, m_vertexShaderSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, m_fragmentShaderSource);

    //Attaches vertex shader
    glAttachShader(program, vs);
    //Attaches fragment shader
    glAttachShader(program, fs);
    //Links Shader
    glLinkProgram(program);
    //Validates the shader is correct
    glValidateProgram(program);
    //Deletes the intermediate shader files
    glDeleteShader(vs);
    glDeleteShader(fs);

    m_Shader = program;
}

Shaders::Shaders(const char* vertexShaderPath, const char* fragmentShaderPath){Load(vertexShaderPath, fragmentShaderPath);}

Shaders::~Shaders()
{
	free((void*)m_vertexShaderSource);
	free((void*)m_fragmentShaderSource);
}
