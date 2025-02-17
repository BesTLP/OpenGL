#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use()
    {
        glUseProgram(ID);
    }
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMatrix4(const std::string& name, GLsizei size,GLboolean flag ,GLfloat* value)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), size, flag, value);
    }
    void setMatrix4(const std::string& name,GLfloat* value)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
    }

    void setVec3(const std::string& filename, GLfloat f1, GLfloat f2, GLfloat f3)
    {
        glUniform3f(glGetUniformLocation(ID, filename.c_str()),f1, f2, f3);
    }

    void setVec3(const std::string& filename, glm::vec3 vec)
    {
        glUniform3f(glGetUniformLocation(ID, filename.c_str()), vec.x, vec.y, vec.z);
    }
private:
    void checkCompileErrors(unsigned int shader, std::string type);

};
#endif