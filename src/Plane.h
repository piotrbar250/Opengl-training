#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "stb_image.h"
#include "Bezier.h"
#include "AssimpObject.h"

using namespace std;
using namespace glm;


random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0f, 1.0f);

class Plane
{
public:

    Shader shader;
    unsigned int VAO, VBO, EBO;
    glm::mat4 model;
    Bezier bezier;
    int vertexCount = 0;
    float denX, denY;
    bool gourand = false;
    AssimpObject tree;
    vector<glm::vec3> treePos;

    Plane() = default;

    Plane(const char* vertexPath, const char* fragmentPath)
        : shader(vertexPath, fragmentPath), model(glm::mat4(1.0f)), tree("../res/vertexAssimpView.glsl", "../res/fragmentAssimpView.glsl", "../res/coconut-tree-obj/coconutTree.obj")
    {
        treePos.resize(4);
       
        for(int i = 0; i < 4; i++)
            treePos[i] = vec3(dis(gen), 0.0f, dis(gen));

        vector<float> vertices;

        float d = 1.f;
        float p = 100.0f;
        float l = d / p;

        float Z = 0.0f;
        float X = 0.0f;

        for(int z = 0; z < p; z++)
        {
            X = 0.0f;
            for(int x = 0; x < p; x++)
            {
                vertexCount += 6;

                glm::vec3 nor;

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);

                X += l;
            }
            Z += l;
        }

        cout << vertexCount << endl;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        shader.use();
        shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shader.setBool("gourand", gourand);       // shader.use();
        // shader.setInt("texture1", 0);
        // shader.setInt("texture2", 1);
    }


    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model, glm::vec3 lightPos, glm::vec3 lightPosJet)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("lightPosJet", lightPosJet);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);


        for(int i = 0; i < 4; i++)
            tree.draw(view, projection, model * translate(mat4(1.0f), vec3(treePos[i].x, bezier.z(treePos[i].x, treePos[i].z), treePos[i].z)) * scale(mat4(1.0f), vec3(0.0005f)), lightPos, lightPosJet);
    }
};