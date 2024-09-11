#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Plane.h"

using namespace std;
class Terrain
{
public:
    int planesCount = 4;
    vector<Plane> planes;
    Terrain()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0f, 1.0f);

        vector<future<void>> futures;
        planes.resize(planesCount);

        for(int i = 0; i < planesCount; i++)
        {
            vector<glm::vec3> treePos(4);
            for(int i = 0; i < 4; i++)
                treePos[i] = vec3(dis(gen), 0.0f, dis(gen));
            //  planes[i] = Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", treePos);
             planes.push_back(Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", treePos));
        }
        // planes.push_back(Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", vector<vec3>(4)));
        // planes[0] = Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", vector<vec3>(4));
        // for(int i = 0; i < planesCount; i++)
        // {
        //     futures.push_back(async(launch::async, [this, i, &gen, &dis](){
        //         vector<glm::vec3> treePos(4);
        //         for(int i = 0; i < 4; i++)
        //             treePos[i] = vec3(dis(gen), 0.0f, dis(gen));

        //         planes[i] = new Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", treePos);
        //         cout << "i " << i << endl;

        //         // planes.push_back(Plane("../res/vertexPlane.glsl", "../res/fragmentPlane.glsl", treePos));
        //     }));
        // }

        // for(auto& f : futures)
        //     f.get();
    }
    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model, glm::vec3 lightPos)
    {
        cout << "hello" << endl;
        planes[0].draw(view, projection, translate(mat4(1.0f), vec3(1.0f, 0.0f, 0.0f)), lightPos);
        cout << "hello2" << endl;
    }
};