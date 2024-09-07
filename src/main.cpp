#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Cube.h"

#include "Textures.h"
#include "stb_image.h"

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window)
{
    // const float cameraSpeed = 0.05f;
    const float cameraSpeed = 2.5 * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraSpeed * normalize(cross(cameraFront, cameraUp));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraSpeed * normalize(cross(cameraFront, cameraUp));
}

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

    glEnable(GL_DEPTH_TEST);

    unsigned int texture1 = textureContainer();
    unsigned int texture2 = textureAwesomeFace();
    
    // Triangle t1;
    // Rectangle r1, r2;
    Cube c1;
    mat4 transform = mat4(1.0f);

    mat4 model = mat4(1.0f);
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
    projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };


    mat4 rot = mat4(1.0f);
    mat4 trans = mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;

        // cout << "Camera Position: " << camX << ", " << 0.0f << ", " << camZ << endl;
        // view = lookAt(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // TEXTURES

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // RENDERING

        // c1.updatePos();
        // c1.draw(view, projection);

        for(int i = 0; i < 10; i++)
        {
            mat4 model = translate(mat4(1.0f), cubePositions[i]) * rotate(mat4(1.0f), (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));
            c1.draw(view, projection, model);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}