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
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int texture1 = textureContainer();
    unsigned int texture2 = textureAwesomeFace();
    
    Triangle t1;
    Rectangle r1, r2;


    mat4 transform = mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEXTURES

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        // TRANSFORMATIONS

        mat4 trans = translate(mat4(1.0f), vec3(0.5f, -0.5f, 0.0f));
        mat4 rot = rotate(mat4(1.0f), (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
        transform = trans * rot;
        // transform = rot * trans;
        r1.shader.setMat4("transform", transform);
        
        // RENDERING
        r1.draw();

        trans = translate(mat4(1.0f), vec3(-0.5f, 0.5f, 0.0f));
        mat4 scal = scale(mat4(1.0f), sin((float)glfwGetTime()) * vec3(1.0f, 1.0f, 1.0f)); 
        transform = trans * scal;
        r2.shader.setMat4("transform", transform);
        
        r2.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}