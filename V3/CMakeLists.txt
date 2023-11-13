cmake_minimum_required(VERSION 3.5)

project(TP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TP main.cpp camera.cpp camera.h controls.cpp controls.h fpscontrols.cpp fpscontrols.h
    navigationcontrols.cpp navigationcontrols.h object.cpp object.h renderer.cpp renderer.h
    shader.cpp shader.h texture.cpp texture.h uvbuffer.cpp uvbuffer.h vertexarray.cpp vertexarray.h
    vertexbuffer.cpp vertexbuffer.h shaders/SimpleFragmentShader.fragmentshader shaders/SimpleVertexShader.vertexshader
    stb_image/stb_image.cpp stb_image/stb_image.h objmodel.h objmodel.cpp pointlight.h pointlight.cpp
    shaders/soleil.fragmentshader shaders/soleil.vertexshader)

target_link_libraries(TP glfw GLEW libGLEW.so libGLU.so libGL.so )
