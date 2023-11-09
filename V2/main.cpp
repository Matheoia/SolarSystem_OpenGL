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

    VertexArray va;
    va.Bind();
    Camera cam(width, height);
    NavigationControls controls(window, &cam);

    //SOLEIL
    Object soleil("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/sun.jpg");
    soleil.position.x = 0;
    soleil.position.y = 0;
    soleil.position.z = 0;

    //MERCURE
    Object mercure("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/mercure.jpg");
    mercure.position.z = -10;

    //VENUS
    Object venus("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/venus.jpg");
    venus.position.z = -20;

    //Terre
    Object terre("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/earth_daymap.jpg");
    terre.position.z = -30;

    //MARS+
    Object mars("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/mars.jpg");
    mars.position.z = -40;

    //JUPITER
    Object jupiter("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/jupiter.jpg");
    jupiter.position.z = -50;

    //SATURNE
    Object saturne("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/saturn.jpg");
    saturne.position.z = -60;

    //URANUS
    Object uranus("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/uranus.jpg");
    uranus.position.z = -70;

    //NEPTUNE
    Object neptune("/home/formation/Documents/OpenGL/TP/models/sphere.obj", path+"/textures/neptune.jpg");
    neptune.position.z = -80;


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
        PointLight light1(lightPosition1, lightColor, lightPower);
        light1.Bind(shader);

        shader.setUniformMat4f("view", cam.getViewMatrix());
        shader.setUniformMat4f("projection", cam.getProjectionMatrix());
        renderer.Clear();

        //SOLEIL

        shader.setUniformMat4f("model", glm::scale(soleil.getModelMatrix(), glm::vec3(10.0f)));
        renderer.Draw(va, soleil, shader);

        //MERCURE
        mercure.rotationAngles.y=currentTime;

        shader.setUniformMat4f("model", glm::scale(soleil.getModelMatrix(), glm::vec3(0.03503604561f)));
        renderer.Draw(va, mercure, shader);

        //VENUS
        venus.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", venus.getModelMatrix());
        renderer.Draw(va, venus, shader);

        //TERRE
        terre.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", terre.getModelMatrix());
        renderer.Draw(va, terre, shader);

        //MARS
        mars.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", mars.getModelMatrix());
        renderer.Draw(va, mars, shader);

        //JUPITER
        jupiter.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", jupiter.getModelMatrix());
        renderer.Draw(va, jupiter, shader);

        //SATURNE
        saturne.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", saturne.getModelMatrix());
        renderer.Draw(va, saturne, shader);

        //URANUS
        uranus.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", uranus.getModelMatrix());
        renderer.Draw(va, uranus, shader);

        //NEPTUNE
        neptune.rotationAngles.y=currentTime;
        shader.setUniformMat4f("model", neptune.getModelMatrix());
        renderer.Draw(va, neptune, shader);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
