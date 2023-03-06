#include <glad/glad.h>
#include<vector>
#include<string>
#include <iostream> 
#include <cstdlib>    
#include "stb_image.h"
#include"texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>

#include<array>
#include"geometry.h"
std::vector<GLfloat> Geometry::GetBoxVertices()
{
    std::vector<GLfloat> boxVertices = {
        -0.5f, -2.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -2.5f, -0.5f, 	1.0f, 0.0f,   // top 
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 0.0f,

        -0.5f, -1.5f, 0.5f, 	1.0f, 0.0f,
        -0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,  // left
        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,
        -0.5f, -1.5f, 0.5f, 	1.0f, 0.0f,

        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,  // right
        0.5f, -2.5f, 0.5f, 	    0.0f, 0.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,

        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -2.5f, 0.5f, 	    1.0f, 0.0f,
        0.5f, -2.5f, 0.5f, 	    1.0f, 0.0f,
        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,  // back 
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,

        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        -0.5f, -1.5f, 0.5f, 	0.0f, 0.0f, // front
        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f
    };
    return boxVertices;
}
std::vector<GLfloat> Geometry::GetPyramidVertices()
{
    std::vector<GLfloat> pyramidVertices = {
         -0.5f, -0.5f, .5f,     0.0f, 0.0f,
         0.5f, -0.5f, .5f,      0.0f, 1.0f,
         -0.5f, 0.5f, .5f,      1.0f, 0.0f,
         0.5f, 0.5f, .5f,       1.0f, 1.0f,
         0.5f, -0.5f, .5f,      0.0f, 1.0f,

         -0.5f, 0.5f, .5f,      1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      0.5f, 0.5f,
         -0.5f, -0.5f, .5f,     0.0f, 0.0f,
         -0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      0.5f, 0.5f,

         -0.5f, 0.5f, .5f,      0.0f, 0.0f,
         0.5f, 0.5f, .5f,       1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      0.5f, 0.5f,
         0.5f, 0.5f, .5f,       0.0f, 0.0f,
         0.5f, -0.5f, .5f,      1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      0.5f, 0.5f,
         0.5f, -0.5f, .5f,      0.0f, 0.0f,
         -0.5f, -0.5f, .5f,     1.0f, 0.0f,
    };

    return pyramidVertices;
}
std::vector<GLfloat> Geometry::GetCompassVertices()
{
    std::vector<GLfloat> compassVertices = {
         0.49f, -0.5f, .5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f, // back rectangle
         0.5f, -0.5f, .5f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
         0.49f, 0.5f, .5f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f, 0.5f, .5f,       0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f, -0.5f, .5f,      0.0f,  0.0f, -1.0f,     0.0f, 1.0f,

         0.49f, 0.5f, .5f,      0.0f,  0.0f,  1.0f,     1.0f, 0.0f,  // bottom
         0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.5f, 0.5f,
         0.49f, -0.5f, .5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,

         0.49f, 0.5f, 0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.5f, 0.5f,
         0.49f, 0.5f, .5f,      -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

         0.5f, 0.5f, .5f,       -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,     // modified pyramid to shift .1 down (y axis modified after camera transformations)
         0.0f, 0.0f, 1.0f,      -1.0f,  0.0f,  0.0f,    0.5f, 0.5f,
         0.5f, 0.5f, .5f,       -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
         0.5f, -0.5f, .5f,      -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.5f, 0.5f,
         0.5f, -0.5f, .5f,      1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.49f, -0.5f, .5f,     1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
    };

    return compassVertices;
}
std::vector<GLfloat> Geometry::GetCubeVertices() 
{
    /* VERTICES */
    std::vector<GLfloat> vertices = {
        -0.5f, -2.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -2.5f, -0.5f, 	1.0f, 0.0f,   // top 
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 0.0f,

        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,
        0.5f, -2.5f, 0.5f, 	    1.0f, 0.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 1.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 1.0f, // bottom 
        -0.5f, -1.5f, 0.5f, 	0.0f, 1.0f,
        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,

        -0.5f, -1.5f, 0.5f, 	1.0f, 0.0f,
        -0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,  // left
        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,
        -0.5f, -1.5f, 0.5f, 	1.0f, 0.0f,

        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,  // right
        0.5f, -2.5f, 0.5f, 	    0.0f, 0.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,

        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -2.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -2.5f, 0.5f, 	    1.0f, 0.0f,
        0.5f, -2.5f, 0.5f, 	    1.0f, 0.0f,
        -0.5f, -2.5f, 0.5f, 	0.0f, 0.0f,  // back 
        -0.5f, -2.5f, -0.5f, 	0.0f, 1.0f,

        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f,
        0.5f, -1.5f, -0.5f, 	1.0f, 1.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        0.5f, -1.5f, 0.5f, 		1.0f, 0.0f,
        -0.5f, -1.5f, 0.5f, 	0.0f, 0.0f, // front
        -0.5f, -1.5f, -0.5f, 	0.0f, 1.0f
    };
    return vertices;
}

std::vector<GLfloat> Geometry::GetSkyboxVertices()
{
    std::vector<GLfloat> skyboxVertices = {
       -1.0f,  1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,

       -1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

       -1.0f, -1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,

       -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,

       -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
        };
    return skyboxVertices;
}

glm::vec3* Geometry::GetPointLightPositions()
{
    static glm::vec3 pointLightPositions[] = {
    glm::vec3(-5.0f, 7.0f, 5.0f),
    glm::vec3(-5.0f, 7.0f, -5.0f),
    glm::vec3(5.0f, 7.0f, 5.0f),
    glm::vec3(5.0f, 7.0f, -5.0f),
    glm::vec3(0.0f, 7.0f, 0.0f),
    glm::vec3(-5.0f, -7.0f, 5.0f),
    glm::vec3(-5.0f, -7.0f, -5.0f),
    glm::vec3(5.0f, -7.0f, 5.0f),
    glm::vec3(5.0f, -7.0f, -5.0f),
    glm::vec3(0.0f, -7.0f, 0.0f),

    };
    return pointLightPositions;
}
glm::vec3* Geometry::GetLightPositions()
{
    static glm::vec3 lightPositions[] = {
    glm::vec3(-3.0f, -1.0f, 3.0f),
    glm::vec3(-3.0f, -1.0f, -3.0f),
    glm::vec3(3.0f, 0.0f, 3.0f),
    glm::vec3(3.0f, 0.0f, -3.0f),
    glm::vec3(0.0f, 4.0f, 0.0f),
    glm::vec3(-3.0f, -4.0f, 3.0f),
    glm::vec3(-3.0f, -4.0f, -3.0f),
    glm::vec3(3.0f, -4.0f, 3.0f),
    glm::vec3(3.0f, -4.0f, -3.0f),
    glm::vec3(0.0f, -4.0f, 0.0f),
    };
    return lightPositions;
}
glm::vec3 Geometry::GetLightPos()
{
    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
    return lightPos;
}


