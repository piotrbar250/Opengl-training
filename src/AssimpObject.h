#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Floor.h"
#include "YAxis.h"
#include "LightningScene.h"

#include "Model-loading/Model.h"
#include "Textures.h"
#include "stb_image.h"


class AssimpObject
{
public:
    Shader ourShader;
    Model ourModel;

    bool gourand = false;
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/A380.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/CRJ-900.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/backpack/backpack.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/airplane-crj-900-cityjet/source/CRJ-900.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/klm-flight-4805/source/boeing_klm_cycles/boeing_klm.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/airplane2/source/airplane_v2_L2_123c71795678-4b63-46c4-b2c6-549c45f4c806/airplane_v2_L2.123c71795678-4b63-46c4-b2c6-549c45f4c806/11805_airplane_v2_L2.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/stylized-tree/source/oak 01.fbx") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/coconut-tree-obj/coconutTree.obj") 
    AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/hawker_900_xp.zip/anadolu_jet.obj") 

    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/cat/cat.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/A380.obj") 
    // AssimpObject(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl", const char* modelPath = "../res/zombie.obj") 
        : ourShader(vertexPath, fragmentPath), ourModel(modelPath)
    {
        // stbi_set_flip_vertically_on_load(true);

        ourShader.use();
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setBool("gourand", gourand);
    }

    void draw(glm::mat4 view, glm::mat4 projection, glm::mat4 model, glm::vec3 lightPos)
    {
        ourShader.use();
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);
        ourShader.setVec3("lightPos", lightPos);

        ourModel.Draw(ourShader);
    }
};