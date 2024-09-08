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
    Backpack() 
        : ourShader("../res/vertexBackpack.glsl", "../res/fragmentBackpack.glsl"),
        ourModel("../res/backpack/backpack.obj")
    {
        stbi_set_flip_vertically_on_load(true);
    }

    void draw(glm::mat4 view, glm::mat4 projection, glm::mat4 model)
    {
        ourShader.use();
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);

        ourModel.Draw(ourShader);
    }
};