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



std::vector<glm::vec3> CreateSphere(float radius, int sectorCount, int stackCount) {
    std::vector<glm::vec3> vertices;

    float x, y, z, xy;
    float sectorStep = 2 * glm::pi<float>() / sectorCount;
    float stackStep = glm::pi<float>() / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = glm::pi<float>() / 2 - i * stackStep;  // range from -pi/2 to pi/2
        xy = radius * cos(stackAngle);  // r * cos(theta)
        z = radius * sin(stackAngle);   // r * sin(theta)

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;  // range from 0 to 2pi
            x = xy * cos(sectorAngle);  // r * cos(theta) * cos(phi)
            y = xy * sin(sectorAngle);  // r * cos(theta) * sin(phi)
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    return vertices;
}



using namespace std;

int main()
{
    string path = "/home/formation/Documents/TP";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

    std::vector<glm::vec3> sphereVertices = CreateSphere(1.0f, 30, 30);

    Object o(sphereVertices, g_uv_buffer_data, path+"/textures/mars.jpg");

//    ObjModel objModel;
//    objModel.LoadFromFile("/home/formation/Documents/TP/models/mars.obj");

//    std::vector<float> vertices = objModel.GetVertexData();
//    int vertexCount = objModel.GetVertexCount();

//    Object o(vertices, g_uv_buffer_data, path+"/textures/mars.jpg");


/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cam.computeMatrices(width, height);
    glm::mat4 m = o.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    glm::mat4 mvp = p*v*m;

    shader.setUniformMat4f("MVP", mvp);


/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

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
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);

        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();
        renderer.Draw(va, o, shader);

        /*o.position.x=2;
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, o, shader);*/

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();




    return 0;
}
