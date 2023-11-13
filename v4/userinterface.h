#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "pointlight.h"
#include "object.h"
#include "shader.h"

class UserInterface
{
public:
    UserInterface(PointLight* light, Object* o, GLFWwindow* window);
    ~UserInterface();
    void Bind(Shader* shader);
    void Draw();
private:
    PointLight* m_pl;
    Object* m_o;
};

#endif // USERINTERFACE_H
