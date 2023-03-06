#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include<vector>
#include<string>
#include <iostream> 
#include <cstdlib>    
#include <glm/glm.hpp>
#include<array>
class Geometry
{
public:
    std::vector<GLfloat> GetBoxVertices();
    std::vector<GLfloat> GetSkyboxVertices();
    std::vector<GLfloat> GetCubeVertices();
    std::vector<GLfloat> GetPyramidVertices();
    std::vector<GLfloat> GetCompassVertices();
    glm::vec3* GetPointLightPositions();
    glm::vec3* GetLightPositions();
    glm::vec3 GetLightPos();

};


#endif