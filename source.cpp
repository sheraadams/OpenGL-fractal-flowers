/*
Copyright (c) 2022 Shera Adams

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Except as contained in this notice, the name(s) of the above copyright holders
shall not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Credit to learnopengl.com for Shader and Camera and Sphere
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include "filesystem.h"
#include "shader.h"
#include "camera.h"
#include "model.h"

#include "petal.h"
#include "flower_stem.h"
#include "sphere.h"
#include "flower_leaf.h"
#include "texture.h"
#include "geometry.h"
#include "objects.h"
int texturePicker;
int t = 0;
int r = 0;
float x = -.0f;
float y = 0.0f;
float z = -0.0f;
/* FUNCTIONS */

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void GetDesktopResolution(float& horizontal, float& vertical);
void ShaderSettings(Shader shader);
/* FUNCTIONS */

/* VARIABLES */
vector<unsigned int> textures;
glm::vec3 viewPos;
double viewX, viewZ;
GLuint  VBO, VAO = 0;
bool Keys[1024];
bool firstMouse = true; 
bool onPerspective = true;
float SCR_WIDTH = 1000;
float SCR_HEIGHT = 900; 
float speed = .1f;
float delta = .1f;
float lastX = (float)SCR_WIDTH / 2.0; 
float lastY = (float)SCR_HEIGHT / 2.0;
float lastFrame = 0.0f;
float deltaTime = 0.0f;
GLfloat rotateX = 0.0f, rotateY = 0.0f, xoffset = 0.0f, yoffset = 0.0f;
glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);
/* VARIABLES */

/* CAMERA */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
/* CAMERA */

void GetDesktopResolution(float& horizontal, float& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int main()
{
    GetDesktopResolution(SCR_WIDTH, SCR_HEIGHT);
    /* GLFW INITIALIZE */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /* GLFW INITIALIZE */

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /* SHADERS */
    Shader lightingShader("simpleVS.vs", "simpleFS.fs");
    Shader skyboxShader("skybox.vs", "skybox.fs");
    Shader greenShader("glsl.vs", "light_green.fs");
    Shader pinkShader("glsl.vs", "light_pink.fs");
    Shader purpleShader("glsl.vs", "light_purple.fs");

    /* VERTICES */
    Geometry geometry;
    std::vector<GLfloat>vertices = geometry.GetCubeVertices();
    std::vector<GLfloat>pyramidVertices = geometry.GetPyramidVertices();
    std::vector<GLfloat>boxVertices = geometry.GetBoxVertices();
    std::vector<GLfloat>skyboxVertices = geometry.GetSkyboxVertices();
    const glm::vec3* lightPositions = geometry.GetLightPositions();
    const glm::vec3* pointLightPositions = geometry.GetPointLightPositions();
    const glm::vec3 lightPos = geometry.GetLightPos();
    
    /*  LIGHT CUBE */
    unsigned int lightCubeVAO, lightCubeVBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(GLfloat), &skyboxVertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(pinkShader.ID, "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(greenShader.ID, "Matrices");
    glUniformBlockBinding(pinkShader.ID, uniformBlockIndexRed, 0);
    glUniformBlockBinding(greenShader.ID, uniformBlockIndexGreen, 0);
    unsigned int uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    /*  LIGHT CUBE */

    /* TEXTURES */
    Textures texture;
    unsigned int heiroTexture = texture.loadTexture("resources/textures/myheiro.png");
    unsigned int cubeTexture = texture.loadTexture("resources/textures/box.png");
    unsigned int planeTexture = texture.loadTexture("resources/textures/1.png");
    unsigned int skyboxTexture = texture.loadTexture("resources/textures/viktorsaznov deepspace.jpeg");

    textures.push_back(heiroTexture);
    textures.push_back(cubeTexture);
    textures.push_back(planeTexture);

    vector<std::string> faces
    {
        "resources/textures/right.jpg", // right 
        "resources/textures/left.jpg", // left 
        "resources/textures/top.jpg", // top  
        "resources/textures/bottom.jpg", // bottom  
        "resources/textures/front.jpg", // front
        "resources/textures/back.jpg", // back
    };
    unsigned int cubemap3Texture = texture.loadCubemap(faces);
    /* TEXTURES */

    /* SET SHADERS */
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    /* SOUND ENGINE */
    //SoundEngine->play2D("LosingControl.mp3", true);

    /* SET THE PROJECTION */
    onPerspective = true;

    /* RENDER LOOP */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* SET SHADER */
        glm::mat4 projection, view, model;
        /* SET PROJECTION
        /****************************************************************/
        if (onPerspective)
            projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        if (!onPerspective)
            projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 1.0f, 100.0f);

        view = camera.GetViewMatrix();
        lightingShader.use();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("model", model);

        /* RENDER SCENE */
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);

        ShaderSettings(lightingShader);
        
        /* CUTOUT BOX */
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spriteColor", color);     
        Objects box;
        box.link5(boxVertices.size() * sizeof(GLfloat), &boxVertices[0]);
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.01f, 0.01f, 0.01f));
        model = glm::translate(model, glm::vec3(0.0f, 16.155, -3.240f));
        model = glm::scale(model, glm::vec3(8.0f, 7.0f , 8.0f));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, skyboxTexture);
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
       
        Objects cube;
        cube.link5(vertices.size() * sizeof(GLfloat), &vertices[0]);
        for (int i = 0; i <= 1; i++)
        {
            if (i == 0)
            {   /* PLANE */
                model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.01f, 0.01f, 0.01f));
               // model = glm::translate(model, glm::vec3(0.0f, -1.255, -3.25));
                model = glm::translate(model, glm::vec3(.00496f, -1.26f, -3.32f));
                model = glm::scale(model, glm::vec3(8.0f, .04f, 8.0f));
                lightingShader.setMat4("model", model);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, planeTexture);
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            if (i == 1)
            { /* FLOWER POT*/
                model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(240.0f), glm::vec3(0.01f, 0.01f, 0.01f));
                model = glm::translate(model, glm::vec3(-2.0f, 1.5f, -1.0f));
                model = glm::scale(model, glm::vec3(.75f, .75f, .65f));
                lightingShader.setMat4("model", model);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, cubeTexture);
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        /* PYRAMIDS */
        Objects pyramid;
        pyramid.link5(pyramidVertices.size() * sizeof(GLfloat), &pyramidVertices[0]);
        float angle = 240.0;
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.01f, 0.01f, 0.01f));
        model = glm::scale(model, glm::vec3(1.75f, 1.75f, 2.25f));
        for (unsigned int i = 0; i < 2; i++)
        {
            if (i == 0)
                model = glm::translate(model, glm::vec3(-2.0f, -1.0f, -1.1f));
            if (i == 1)
                model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
            lightingShader.setMat4("model", model);
            // use the already bound cube texture
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // use flower texture on the following objects 
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, heiroTexture);
        //color = glm::vec4(redValue, 0.0f, blueValue, 1.0f);
        //lightingShader.setVec3("spriteColor", color);
        model = glm::mat4(1.0f);
        for (int i = 0; i <= 5; i++)
        {
            model = glm::mat4(.8f);
            model = glm::rotate(model, glm::radians(72.0f * i), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-0.00504, -0.124999, -2.04));
            model = glm::scale(model, glm::vec3(.5f, .5f, .5f));
            lightingShader.setMat4("model", model);
            Petal petal;
            petal.Draw();
        }

        model = glm::translate(model, glm::vec3(-.00040014, -2.70001, -.02f));
        lightingShader.setMat4("model", model);
        FlowerStem flowerStem;
        flowerStem.Draw();

        model = glm::translate(model, glm::vec3(-0.0f, 0.22f, -0.1f));
        lightingShader.setMat4("model", model);
        Sphere sphere;
        sphere.Draw();

        model = glm::translate(model, glm::vec3(-0.0f, 0.455f, 0.17f));
        lightingShader.setMat4("model", model);
        FlowerLeaf leaf;
        leaf.Draw();

        /* RENDER LIGHTS */
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glBindVertexArray(lightCubeVAO);
        float speed = 45.0f;
        float direction = -1.0;
        for (unsigned int i = 0; i < 2; i++)
        {
            if (i == 1)
            { /* PINK LIGHTS */
                pinkShader.use();
                pinkShader.setMat4("projection", projection);
                pinkShader.setMat4("view", view);
                model = glm::mat4(1.0f);
                model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(speed) * direction * 2.0f, glm::vec3(0.0f, 1.0f, 0.f));
                model = glm::translate(model, lightPositions[i]);
                model = glm::scale(model, glm::vec3(.25f));
                pinkShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            else
            { /* PURPLE LIGHTS */
                purpleShader.use();
                purpleShader.setMat4("projection", projection);
                purpleShader.setMat4("view", view);
                model = glm::mat4(1.0f);
                model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(speed) * 2.0f, glm::vec3(0.0f, 1.0f, 0.f));
                model = glm::translate(model, lightPositions[i]);
                model = glm::scale(model, glm::vec3(.25f));
                purpleShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        /* RENDER LIGHTS */

        /* RENDER SKYBOX */
        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        Objects skybox;
        skybox.skybox(skyboxVertices.size() * sizeof(GLfloat), &skyboxVertices[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap3Texture);
        glDrawArrays(GL_TRIANGLES, 0, 72);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* SWAP BUFFERS AND DELETE VAOS FROM MEMORY */
    Petal petal;
    petal.~Petal();
    FlowerStem flowerStem;
    flowerStem.~FlowerStem();
    Sphere sphere;
    sphere.~Sphere();
    FlowerLeaf leaf;
    leaf.~FlowerLeaf();
  
    Objects cube;
    cube.clear();
    Objects box;
    box.clear();
    Objects pyramid;
    pyramid.clear();
    Objects pyramid2;
    pyramid2.clear();
    Objects skybox;
    skybox.clear();

    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &lightCubeVBO);

    glDeleteTextures(1, &heiroTexture);
    glDeleteTextures(1, &planeTexture);
    glDeleteTextures(1, &cubemap3Texture);
    glDeleteTextures(1, &cubeTexture);
    glDeleteShader(lightingShader.ID);
    glDeleteShader(greenShader.ID);
    glDeleteShader(purpleShader.ID);
    glDeleteShader(skyboxShader.ID);
    glDeleteShader(pinkShader.ID);

    glfwTerminate();
    return 0;
}

/* PROCESS INPUT */
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime); 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS))
        onPerspective = false;
    if ((glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS))
        onPerspective = true;
    if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
        x -= .005;
    if ((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
        x += .005;
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
        y += .005;
    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
        y -= .005;
    if ((glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS))
        z -= .005;
    if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS))
        z += .005;
    if ((glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS))
        std::cout << "( " << x << "f, " << y << "f, " << z << "f)" << std::endl;
    if ((glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS))
    {
        if (t < textures.size() -1)
        {
            t += 1;
            texturePicker = textures[t];
        }
        else 
            t = 0;
    }
    if ((glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS))
    {
        if (r < textures.size() -1)
        {
            r += 1;
            texturePicker = textures[r];
        }
        else
            r = 0;
    }
    
}

/* CALLBACKS */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void ShaderSettings(Shader shader)
{
    shader.setInt("spriteColor", 3);
    int vertexColorLocation = glGetUniformLocation(shader.ID, "color");
}