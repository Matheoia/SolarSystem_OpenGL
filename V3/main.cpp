#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
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
    string path = "/home/formation/Documents/OpenGL/TP";

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

    Shader shaderSoleil(path+"/shaders/soleil.vertexshader", path+"/shaders/soleil.fragmentshader");


    VertexArray va;
    va.Bind();
    Camera cam(width, height);
    NavigationControls controls(window, &cam);


    Object stars("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/stars.jpg");
    stars.position.x = 0;
    stars.position.y = 0;
    stars.position.z = 0;

    //SOLEIL
    Object soleil("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/sun.jpg");
    soleil.position.x = 0;
    soleil.position.y = 0;
    soleil.position.z = 0;

    //MERCURE
    Object mercure("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/mercure.jpg");
    mercure.position.z = -20;

    //VENUS
    Object venus("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/venus.jpg");
    venus.position.z = -30;

    //Terre
    Object terre("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/earth_daymap.jpg");
    terre.position.z = -40;

    //MARS+
    Object mars("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/mars.jpg");
    mars.position.z = -55;

    //JUPITER
    Object jupiter("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/jupiter.jpg");
    jupiter.position.z = -160;

    //SATURNE
    Object saturne("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/saturn.jpg");
    saturne.position.z = -280;
    Object anneauSaturne("/home/formation/Documents/OpenGL/TP/models/anneau.obj", path+"/textures/saturn_ring.png");
    anneauSaturne.position.z=-280;

    //URANUS
    Object uranus("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/uranus.jpg");
    uranus.position.z = -580;

    //NEPTUNE
    Object neptune("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/neptune.jpg");
    neptune.position.z = -880;

    Object ellipse("/home/formation/Documents/OpenGL/TP/models/orbite.obj", path+"/textures/blanc.jpg");


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
        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);

        glm::vec3 lightPosition1(0.0f, 0.0f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float lightPower = 1.0f;
        PointLight light(lightPosition1, lightColor, lightPower);
        light.Bind(shader);

        shader.setUniformMat4f("view", cam.getViewMatrix());
        shader.setUniformMat4f("projection", cam.getProjectionMatrix());

        renderer.Clear();

        //MERCURE
        mercure.rotationAngles.y=currentTime/59/4;
        mercure.position.x = -20.0f * cos(currentTime * 2.0f * glm::pi<float>() / 88.0f);
        mercure.position.z = -20.0f * sin(currentTime * 2.0f * glm::pi<float>() / 88.0f);
        shader.setUniformMat4f("model", glm::scale(mercure.getModelMatrix(), glm::vec3(0.40f)));
        renderer.Draw(va, mercure, shader);

        //VENUS
        venus.rotationAngles.y= currentTime/243/4;
        venus.position.x = 30.0f *  cos(currentTime * 2.0f * glm::pi<float>() / 225.0f);
        venus.position.z = 30.0f *  sin(currentTime * 2.0f * glm::pi<float>() / 225.0f);
        shader.setUniformMat4f("model", glm::scale(venus.getModelMatrix(), glm::vec3(0.94f)));
        renderer.Draw(va, venus, shader);

        //TERRE
        terre.rotationAngles.y=currentTime/4;
        terre.position.x = -40.0f * cos(currentTime * 2.0f * glm::pi<float>() / 365.25f);
        terre.position.z = -40.0f * sin(currentTime * 2.0f * glm::pi<float>() / 365.25f) /** 0.01671123f*/;
        shader.setUniformMat4f("model", terre.getModelMatrix());
        renderer.Draw(va, terre, shader);

        //MARS
        mars.rotationAngles.y=currentTime/1.025/4;
        mars.position.x = 55.0f * cos(currentTime * 2.0f * glm::pi<float>() / 687.0f);
        mars.position.z = 55.0f * sin(currentTime * 2.0f * glm::pi<float>() / 687.0f);
        shader.setUniformMat4f("model", glm::scale(mars.getModelMatrix(), glm::vec3(0.53f)));
        renderer.Draw(va, mars, shader);

        //JUPITER
        jupiter.rotationAngles.y=currentTime/0.42/4;
        jupiter.position.x = -160.0f * cos(currentTime * 2.0f * glm::pi<float>() / 4328.9f);
        jupiter.position.z = -160.0f * sin(currentTime * 2.0f * glm::pi<float>() / 4328.0f);
        shader.setUniformMat4f("model", glm::scale(jupiter.getModelMatrix(), glm::vec3(10.97f)));
        renderer.Draw(va, jupiter, shader);

        //SATURNE
        saturne.rotationAngles.y=currentTime/0.4/4;
        saturne.position.x = 280.0f * cos(currentTime * 2.0f * glm::pi<float>() / 10752.9f);
        saturne.position.z = 280.0f * sin(currentTime * 2.0f * glm::pi<float>() / 10752.9f);
        shader.setUniformMat4f("model", glm::scale(saturne.getModelMatrix(), glm::vec3(9.14f)));
        renderer.Draw(va, saturne, shader);

        anneauSaturne.rotationAngles.y=currentTime/0.4/4;
        anneauSaturne.position.x = 280.0f * cos(currentTime * 2.0f * glm::pi<float>() / 10752.9f);
        anneauSaturne.position.z = 280.0f * sin(currentTime * 2.0f * glm::pi<float>() / 10752.9f);
        shader.setUniformMat4f("model", glm::scale(anneauSaturne.getModelMatrix(), glm::vec3(9.14f)));
        renderer.Draw(va, anneauSaturne, shader);

        //URANUS
        uranus.rotationAngles.y=currentTime/0.7/4;
        uranus.position.x = -580.0f * cos(currentTime * 2.0f * glm::pi<float>() / 30660.0f);
        uranus.position.z = -580.0f * sin(currentTime * 2.0f * glm::pi<float>() / 30660.0f);
        shader.setUniformMat4f("model", glm::scale(uranus.getModelMatrix(), glm::vec3(3.98f)));
        renderer.Draw(va, uranus, shader);

        //NEPTUNE
        neptune.rotationAngles.y=currentTime/0.66/4;
        neptune.position.x = 880.0f * cos(currentTime * 2.0f * glm::pi<float>() / 61243.35f);
        neptune.position.z = 880.0f * sin(currentTime * 2.0f * glm::pi<float>() / 61243.35f);
        shader.setUniformMat4f("model", glm::scale(neptune.getModelMatrix(), glm::vec3(3.86f)));
        renderer.Draw(va, neptune, shader);

        shaderSoleil.Bind();

        //SOLEIL ETOILES ORBITES
        soleil.rotationAngles.y=currentTime/25/4;
        shaderSoleil.setUniformMat4f("camMatrix", cam.getProjectionMatrix() * cam.getViewMatrix());
        shaderSoleil.setUniformMat4f("model", glm::scale(soleil.getModelMatrix(), glm::vec3(10.0f)));
        renderer.Draw(va, soleil, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(stars.getModelMatrix(), glm::vec3(2000.0f)));
        renderer.Draw(va, stars, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(20.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(30.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(40.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(55.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(160.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(280.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(580.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        shaderSoleil.setUniformMat4f("model", glm::scale(ellipse.getModelMatrix(), glm::vec3(880.0f)));
        renderer.Draw(va, ellipse, shaderSoleil);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
