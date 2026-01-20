#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* basicShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =" #version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; 

void checkCompileErrors(const unsigned int vertexShader, const unsigned int shaderProgram){
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "SHADER COMPILATION ERROR: \n" << infoLog << std::endl; 
    }
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<< "SHADER PROGRAM ERROR: \n" << infoLog << std::endl;
    }
    
    
}