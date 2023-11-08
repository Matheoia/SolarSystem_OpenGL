#include "pointlight.h"

PointLight::PointLight(glm::vec3& position, glm::vec3& color, float power)
    :position(position), color(color), power(power)
{
}

PointLight::~PointLight() {}

void PointLight::Bind(Shader& shader)
{
    shader.Bind();
    shader.setUniform3fv("lightPosition", position);
    shader.setUniform3fv("lightColor", color);
    shader.setUniform1f("lightPower", power);
//    GLuint shaderProgramID = shader.GetRendererID();
//    glUseProgram(shaderProgramID);

//    glUniform3f(glGetUniformLocation(shaderProgramID, "pointLight.position"), position);
//    glUniform3f(glGetUniformLocation(shaderProgramID, "pointLight.color"), color.x, color.y, color.z);
//    glUniform1f(glGetUniformLocation(shaderProgramID, "pointLight.power"), power);

}

void PointLight::Unbind()
{

}
