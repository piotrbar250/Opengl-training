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

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TEXTURES

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        // TRANSFORMATIONS

        // mat4 trans = translate(mat4(1.0f), vec3(0.5f, -0.5f, 0.0f));
        // mat4 rot = rotate(mat4(1.0f), (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
        // transform = trans * rot;
        // // transform = rot * trans;
        // r1.shader.setMat4("transform", transform);
        
        // RENDERING

        // model = rotate(mat4(1.0f), glm::radians(-55.0f) , vec3(1.0f, 0.0f, 0.0f));
        // model = scale(mat4(1.0f), vec3(100.0f, 100.0f, 0.0f));
        // view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
        // projection = perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // projection = ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        // projection = ortho(0.0f, 800.0f, 0.0f, 600.0f);
        // glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // glm::mat4 view          = glm::mat4(1.0f);
        // glm::mat4 projection    = glm::mat4(1.0f);
        // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        // model = rotate(mat4(1.0f), -float(glfwGetTime()), vec3(1.0f, 0.0f, 0.0f));
        // model = rotate(mat4(1.0f), radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

        // view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
        // projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);


        // r1.shader.use();
        // r1.shader.setMat4("model", model);
        // r1.shader.setMat4("view", view);
        // r1.shader.setMat4("projection", projection);
        // mat4 model = rotate(mat4(1.0f), radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
        float tim = (float)glfwGetTime();
        mat4 model = rotate(mat4(1.0f), (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));
        // c1.draw(view, projection, model);

        for(int i = 0; i < 10; i++)
        {
            mat4 model = translate(mat4(1.0f), cubePositions[i]) * rotate(mat4(1.0f), tim, vec3(1.0f, 1.0f, 1.0f));
            c1.draw(view, projection, model);
        }


        // trans = translate(mat4(1.0f), vec3(-0.5f, 0.5f, 0.0f));
        // mat4 scal = scale(mat4(1.0f), sin((float)glfwGetTime()) * vec3(1.0f, 1.0f, 1.0f)); 
        // transform = trans * scal;
        // r2.shader.setMat4("transform", transform);
        
        // r2.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}