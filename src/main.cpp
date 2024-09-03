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
#include "Misc.h"

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
    Rectangle r1;


    vec4 vec1(1.0f, 4.0f, 4.0f, 1.0f);
    vec4 vec2(vec1);
    vec4 vec12(vec1);
    vec4 vec22(vec1);


    mat4 trans = mat4(1.0f);
    mat4 scal = mat4(1.0f);

    trans = translate(trans, vec3(1.0f, 2.0f, 3.0f));
    scal = scale(scal, vec3(2.0f, 2.0f, 2.0f));

    vec1 = scal * vec1;
    vec1 = trans * vec1;
    cout << vec1.x << " " << vec1.y << " " << vec1.z << endl;

///////////////////////////////////
    vec2 = trans * vec2;
    vec2 = scal * vec2;
    cout << vec2.x << " " << vec2.y << " " << vec2.z << endl;

///////////////////////////////////
    mat4 tr = trans * scal;
    vec12 = tr * vec12;
    cout << vec12.x << " " << vec12.y << " " << vec12.z << endl;

///////////////////////////////////
    mat4 tr2 = scal * trans;
    vec22 = tr2 * vec22;
    cout << vec22.x << " " << vec22.y << " " << vec22.z << endl;

    // printMat4(tr);
    // printMat4(tr2);

    // printMat4(scal);
    // printMat4(trans);
    // printMat4(scal * trans);


    // printMat4(trans);

    // cout << trans[3][0] << endl;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEXTURES

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        // RENDERING
        r1.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}