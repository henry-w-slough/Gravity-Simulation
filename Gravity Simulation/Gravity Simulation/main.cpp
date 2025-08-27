#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main(void)
{
    //initializing both GLFW and GLAD
    glfwInit();


   
    //globals
    GLFWwindow* window;

    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 800;


    
    //vertex shader sources
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
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n";
        "}\n";
        



    //window declaration
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravity Simulation", NULL, NULL);


    //error check for if the window can't be created
    if (!window)
    {
        std::cout << "Window failed to create" << std::endl;
        glfwTerminate();
        return -1;
    }
        
    //make the created window THE window.
    glfwMakeContextCurrent(window);



    //error throw for GLAD during it's initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //set the size of the screen for GLAD after it's initialization
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



    //vertices are in xyz format and positions are %'s of the screen width and height
    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };


    //vertex buffer object stuff

    unsigned int VBO;

    //buffer object used for data sent for displaying
    glGenBuffers(1, &VBO);

    //bind the buffer of type GL_ARRAY_BUFFER to VBO object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //sending the data for the vertices to the buffer. 
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);




    //vertex shader stuff

    unsigned int vertexShader;
    //pretty self explanatory. Shader type for argument
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //attaching vertexShaderSource to vertexShader

    glCompileShader(vertexShader);




    //fragment shader for calculating color of the pixels
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);











    //Loop until the user closes the window  
    while (!glfwWindowShouldClose(window))
    {

        
        //clearing screen 
        glClear(GL_COLOR_BUFFER_BIT);
        //setting background color
        glClearColor(0.2, 0.2, 0.2, 0);

        //swap front and back buffers (flip)
        glfwSwapBuffers(window);

        //poll for process events
        glfwPollEvents();
    }





    glfwTerminate();
    return 0;
}