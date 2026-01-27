#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "models.hpp"
#include "shaders.hpp"

const std::string SHADER_PATH = "./resources/shaders/";

void resizeCallback(GLFWwindow*, int width, int height){
    glViewport(0, 0, width, height);
}
void cursorMovedCallback(GLFWwindow* window, double x, double y){
   // std::cout << "Cursor moved: x: " << x <<  std::endl << "y: " << y << std::endl; 
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

void selectShape(const Shape shape, float** vertices, unsigned int** indices, unsigned int** sizes){
    switch (shape)
    {
    case TRIANGLE:
        *vertices = new float[18]
        {
           -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        *indices = new unsigned int[3]{
            0,1,2
        };
        *sizes = new unsigned int[2]{
            18, 3
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);
    delete(vertices);
    delete(indices);
    delete(sizes);
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

    unsigned int VBO, VAO,EBO;
    renderShape(&VAO, &VBO, &EBO);
    Shader shader((SHADER_PATH + "vertexUpDown.vs").c_str(), (SHADER_PATH + "fragment.fs").c_str());


    char in;
    bool render = false;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &render);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        shader.setFloat("offset", 0.5f);
        if (render){
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}