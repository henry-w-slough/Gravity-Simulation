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


    const void clear() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(SCR_COLOR[0], SCR_COLOR[1], SCR_COLOR[2], SCR_COLOR[3]);
    }


    void update(unsigned int shaderProgram, unsigned int VAO) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
    }

    void addVertexData(unsigned int bufferOperation, float vertices[], unsigned int drawOperation) {
        glBufferData(bufferOperation, sizeof(vertices), vertices, drawOperation);
    }

    void pointVertexAttr(int index, int size, unsigned int dataType, unsigned int normalized, int stride, void* offset) {
        glVertexAttribPointer(index, size, dataType, normalized, stride, offset);
        glEnableVertexAttribArray(index);
    }

    void bindBuffer(unsigned int bufferOperation, int buffer) {
        glBindBuffer(bufferOperation, buffer);
    }
};






struct Shader {
    const char* shaderSource;
    const GLenum shaderType;

    unsigned int shader;



    //used to create and compile a new shader
    void generate() {
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        //error checking
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            std::cout << "ERROR: Shader creation failed: " + to_string(shader) << endl;

            destroy();
            return;
        }

    }

    const void destroy() const {
        glDeleteShader(shader);
    }

};






struct ShaderProgram {
    unsigned int program = glCreateProgram();

    void attachShader(unsigned int shader) const {
        glAttachShader(program, shader);
    }

    const void link() const {
        glLinkProgram(program);

        // check for linking errors
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            cout << "ERROR: Shader program linking failed: " + to_string(program) << endl;
            return;
        }
    }

    const void destroy() const {
        glDeleteProgram(program);
    }
};






struct VertexBufferObject {
    unsigned int buffer;

    void generate(int size) {
        glGenBuffers(size, &buffer);
    }

    void bind(unsigned int bufferOperation) {
        glBindBuffer(bufferOperation, buffer);
    }

    void destroy() {
        glDeleteBuffers(1, &buffer);
    }

    void unbind() {
        glBindVertexArray(0);
    }
};



struct VertexArrayObject {
    unsigned int array;

    void generateArray(int size) {
        glGenVertexArrays(size, &array);
    }

    void bind() {
        glBindVertexArray(array);
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void destroy() {
        glDeleteVertexArrays(1, &array);
    }

};
