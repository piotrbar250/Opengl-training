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


class Backpack
{
public:
    Shader ourShader;
    Model ourModel;

    bool gourand = false;
    Backpack() 
        : ourShader("../res/vertexBackpack.glsl", "../res/fragmentBackpack.glsl"),
        // ourModel("../res/backpack/backpack.obj")
        ourModel("../res/zombie.obj")
    {
        stbi_set_flip_vertically_on_load(true);

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