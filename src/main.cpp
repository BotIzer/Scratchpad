#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "models.hpp"
#include "shaders.hpp"

void resizeCallback(GLFWwindow*, int width, int height){
    glViewport(0, 0, width, height);
}
void cursorMovedCallback(GLFWwindow* window, double x, double y){
    std::cout << "Cursor moved: x: " << x <<  std::endl << "y: " << y << std::endl; 
}

void processInput(GLFWwindow* window, bool* render){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        *render = true;
        std::cout << "T Press";
    }
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
    {
        *render = false;
    }
    
    
    
}
void createShader(unsigned int* shaderProgram){

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &basicShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void selectShape(const Shape shape, float** vertices, unsigned int** indices, unsigned int** sizes){
    switch (shape)
    {
    case TRIANGLE:
        *vertices = new float[9]
        {
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f 
            //-0.8f, -0.5f, 0.0f,
            //-0.3f, -0.5f, 0.0f,
            //-0.55f, 0.3f, 0.0f,

            //0.8f, -0.5f, 0.0f,
            //0.3f, -0.5f, 0.0f,
            //0.55f, 0.3f, 0.0f
        };
        *indices = new unsigned int[3]{
            0,1,2//,3,4,5
        };
        *sizes = new unsigned int[2]{
            9,3
            //18,6
        };
        break;
    
    case RECTANGLE:
        *vertices = new float[12]
        {
            0.5f,  0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f, 
           -0.5f, -0.5f, 0.0f,
           -0.5f,  0.5f, 0.0f
        };
        *indices = new unsigned int[6]{
            0,1,3,
            1,2,3
        };
        *sizes = new unsigned int[2]{
            12,6
        };
        break;
    default:
        *vertices = new float[9]
        {
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f 
        };
        break;
    }
}

void renderShape(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO){

    float* vertices;
    unsigned int* indices, *sizes;
    selectShape(TRIANGLE, &vertices, &indices, &sizes);


    glGenVertexArrays(1, VAO);
    glGenBuffers(1,VBO);
    glGenBuffers(1, EBO);
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizes[0] * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizes[1] * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);
    delete(vertices);
    delete(indices);
    delete(sizes);
}

void renderShape2(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO2, unsigned int* VBO2, unsigned int* EBO2){

    float vertices1[] = {

            -0.8f, -0.5f, 0.0f,
            -0.3f, -0.5f, 0.0f,
            -0.55f, 0.3f, 0.0f,

    };
    unsigned int indices1[] = {
        0,1,2
    };
    float vertices2[] = {

            0.8f, -0.5f, 0.0f,
            0.3f, -0.5f, 0.0f,
            0.55f, 0.3f, 0.0f
    };
    unsigned int indices2[] = {
        0,1,2
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1,VBO);
    glGenBuffers(1, EBO);
    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, VAO2);
    glGenBuffers(1, VBO2);
    glGenBuffers(1, EBO2);
    glBindVertexArray(*VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

}
int main(){

    dimensions viewport = {800, 600};
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(viewport.width,viewport.height, "Scratchpad", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl; 
        return -1;
    }
    glViewport(0,0, viewport.width, viewport.height); 
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetCursorPosCallback(window, cursorMovedCallback);

    unsigned int VBO, VAO,EBO, shaderProgram;
    unsigned int VBO2, VAO2, EBO2;
    createShader(&shaderProgram);
    //renderShape(&VAO, &VBO, &EBO);
    renderShape2(&VAO, &VBO, &EBO, &VAO2, &VBO2, &EBO2);

    char in;
    bool render = false;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &render);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        if (render){
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAO2);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO2);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}