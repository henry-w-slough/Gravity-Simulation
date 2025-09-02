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
    Shader vertexShader = {vertexShaderSource, GL_VERTEX_SHADER};
    vertexShader.generate();

    Shader fragmentShader = { fragmentShaderSource, GL_FRAGMENT_SHADER };
    fragmentShader.generate();



    //shader program object + program
    ShaderProgram shaderProgram;

    //attaching shaders to
    shaderProgram.attachShader(vertexShader.shader);
    shaderProgram.attachShader(fragmentShader.shader);

    shaderProgram.link();





    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         -0.5f,  0.5f, 0.0f  // top   
    };



    //setting up vertex buffer object + vertex array object
    VertexBufferObject VBO;
    VBO.generate(1);

    VertexArrayObject VAO;
    VAO.generateArray(1);

    //binding VAO and GL directly, and VBO with VAO through buffer
    VAO.bind();
    VBO.bind(GL_ARRAY_BUFFER);



    screen.addVertexData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
    screen.pointVertexAttr(0, sizeof(vertices), GL_VERTEX_ARRAY, GL_FALSE, 3 * sizeof(float), (void*)0);


    //UNBINDING VBO and VAO buffer
    VAO.unbind();
    VBO.unbind();





    while (!glfwWindowShouldClose(window))
    {
        

    }





    VAO.destroy();
    VBO.destroy();
    


    shaderProgram.destroy();

    glfwTerminate();
    return 0;
}







