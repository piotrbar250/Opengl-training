#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Triangle.h"
#include "Rectangle.h"

#include "Textures.h"
#include "stb_image.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int texture1 = textureContainer();
    unsigned int texture2 = textureAwesomeFace();
    
    Triangle t1;
    Rectangle r1;



    while (!glfwWindowShouldClose(window))
    {
        cout << mixValue << endl;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEXTURES
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // RENDERING
        r1.shader.setFloat("mixValue", mixValue);
        r1.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP)
    {
        mixValue += 0.01f;
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }

    if (key == GLFW_KEY_DOWN)
    {
        mixValue -= 0.01;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
}