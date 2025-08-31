#define GLFW_INCLUDE_NONE
#include <iostream>

#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

//used for error checking
int success;


using namespace std;



struct Screen {
    int SCR_WIDTH;
    int SCR_HEIGHT;
    const float SCR_COLOR[4];
    const char* windowTitle;

    GLFWwindow* window;


	GLFWwindow* initGlfwWindow() {
        //stopping screen resizing (because I'm too lazy to adjust to new sizes)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowTitle, NULL, NULL);

        //error checking
        if (window == NULL)
        {
           cout << "ERROR: Failed to create GLFW window" << endl;
           glfwTerminate();
        }

        else {
            glfwMakeContextCurrent(window);
            return window;
        }
    }


    const void clearScreen() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(SCR_COLOR[0], SCR_COLOR[1], SCR_COLOR[2], SCR_COLOR[3]);
    }


    void updateScreen(unsigned int shaderProgram, unsigned int VAO) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
    }
};






struct Shader {
    const char* shaderSource;
    const GLenum shaderType;

    unsigned int shader;



    //used to create and compile a new shader
    void createShader() {
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        //error checking
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            std::cout << "ERROR: Shader creation failed: " + to_string(shader) << endl;

            destroyShader();
            return;
        }

    }

    const void destroyShader() const {
        glDeleteShader(shader);
    }

};






struct ShaderProgram {
    unsigned int program = glCreateProgram();

    void attachShader(unsigned int shader) const {
        glAttachShader(program, shader);
    }

    const void linkProgram() const {
        glLinkProgram(program);

        // check for linking errors
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            cout << "ERROR: Shader program linking failed: " + to_string(program) << endl;
            return;
        }
    }

    const void destroyProgram() const {
        glDeleteProgram(program);
    }
};
