#define GLFW_INCLUDE_NONE
#include <iostream>

#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ScreenAttributes.h"

using namespace std;




const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.1f, 0.4f, 0.3f, 1.0f);\n"
"}\n\0";








int main()
{
    glfwInit();

    //used for error checks
    int success;

     
    //object for all window-related operations
    Screen screen = {800, 800, { 0.1f, 0.1f, 0.1f, 1.0f }, "Gravity Simulation"};

    screen.SCR_WIDTH = 800;
    screen.SCR_HEIGHT = 800;

    GLFWwindow* window = screen.initGlfwWindow();


    //loading glad and error handling
    success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!success) {
        cout << "ERROR: Failed to load GLAD library!" << endl;
    }
    
    
    //object to reference and control vertex shader
    Shader vertexShaderOBJ = {vertexShaderSource, GL_VERTEX_SHADER};
    vertexShaderOBJ.createShader();
    unsigned int vertexShader = vertexShaderOBJ.shader;

    Shader fragmentShaderOBJ = { fragmentShaderSource, GL_FRAGMENT_SHADER };
    fragmentShaderOBJ.createShader();
    unsigned int fragmentShader = fragmentShaderOBJ.shader;




    ShaderProgram shaderProgramOBJ;
    unsigned int shaderProgram = shaderProgramOBJ.program;

    shaderProgramOBJ.attachShader(vertexShader);
    shaderProgramOBJ.attachShader(fragmentShader);

    shaderProgramOBJ.linkProgram();







   


    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         -0.5f,  0.5f, 0.0f  // top   
    };







    //setting up vertex buffer object + vertex array object
    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);






    while (!glfwWindowShouldClose(window))
    {
        



        screen.clearScreen();
        screen.updateScreen(shaderProgram, VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }






    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    


    shaderProgramOBJ.destroyProgram();

    glfwTerminate();
    return 0;
}







