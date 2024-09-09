#pragma once
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "stb_image.h"

using namespace std;

class Plane
{
public:
    Shader shader;
    unsigned int VAO, VBO, EBO;
    glm::mat4 model;

    int vertexCount = 0;
    float denX, denY;

    Plane(const char* vertexPath = "../res/vertexPlane.glsl", const char* fragmentPath = "../res/fragmentPlane.glsl")
        : shader(vertexPath, fragmentPath), model(glm::mat4(1.0f))
    {
        // float r = 5.0f;
        // denX = 10.0f;
        // denY = 10.0f;

        // float vertices[] = {
        //     -r, 0.0f, r, 
        //     -r, 0.0f, -r,
        //     r, 0.0f, r,

        //     r, 0.0f, r,
        //     r, 0.0f, -r,
        //     -r, 0.0f, -r,
        // };

        vector<float> vertices;

        float d = 10.f;
        float p = 5.0f;
        float l = d / p;

        float Z = 0.0f;
        float X = 0.0f;

        for(int z = 0; z < 5; z++)
        {
            X = 0.0f;
            for(int x = 0; x < 5; x++)
            {
                vertexCount += 6;

                vertices.push_back(X);
                vertices.push_back(0.0f);
                vertices.push_back(-Z);

                vertices.push_back(X + l);
                vertices.push_back(0.0f);
                vertices.push_back(-Z);

                vertices.push_back(X);
                vertices.push_back(0.0f);
                vertices.push_back(-(Z + l));

                vertices.push_back(X);
                vertices.push_back(0.0f);
                vertices.push_back(-(Z + l));

                vertices.push_back(X + l);
                vertices.push_back(0.0f);
                vertices.push_back(-(Z + l));

                vertices.push_back(X + l);
                vertices.push_back(0.0f);
                vertices.push_back(-Z);

                X += l;
            }
            Z += l;
        }

        for(int i = 0; i < vertices.size(); i += 3)
            cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;


        cout << vertexCount << endl;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        // shader.use();
        // shader.setInt("texture1", 0);
        // shader.setInt("texture2", 1);
    }


    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
};