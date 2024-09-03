#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void printMat4(glm::mat4 mat)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            std::cout << mat[j][i] << " ";
        }
        std::cout << std::endl;
    }

}