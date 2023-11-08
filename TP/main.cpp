#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "objmodel.h"

#include "pointlight.h"

using namespace std;

int main()
{
    string path = "/home/formation/Documents/TP";

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

    Renderer renderer;


    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

    VertexArray va;
    va.Bind();

    Camera cam(width, height);
    NavigationControls controls(window, &cam);


    vector<glm::vec3> g_vertex_buffer_data = {
        glm::vec3(-1.0f,-1.0f,-1.0f), // triangle 1 : begin
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), // triangle 1 : end
        glm::vec3(1.0f, 1.0f,-1.0f), // triangle 2 : begin
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f), // triangle 2 : end
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f)
    };

    vector<glm::vec2> g_uv_buffer_data = {
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.000004f, 1.0f-0.671870f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.667979f, 1.0f-0.335851f)
    };

    Object o(g_vertex_buffer_data, g_uv_buffer_data, path+"/textures/mars.jpg");


    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;

        o.rotationAngles.y=currentTime;
        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);

        glm::vec3 lightPosition(-10.0f, -10.0f, -10.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        PointLight light(lightPosition, lightColor, 1.0f);
        shader.setUniform3fv("lightColor", light.color);
        shader.setUniform3fv("lightPosition", lightPosition);
//        light.Bind(shader);

        shader.setUniformMat4f("model", o.getModelMatrix());
        shader.setUniformMat4f("view", cam.getViewMatrix());
        shader.setUniformMat4f("projection", cam.getProjectionMatrix());
        renderer.Clear();
        renderer.Draw(va, o, shader);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
