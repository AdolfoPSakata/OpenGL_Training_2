#include <UniformsManager.h>

UniformManager::UniformManager()
{
}

UniformManager::~UniformManager()
{
}

GLint UniformManager::PreProcessUniforms(GLint& id, std::string uniformString)
{
       GLint location = glGetUniformLocation(id, uniformString.c_str());

       if (location >= 0)
       {
           std::cout << " UNIFORM: " << uniformString  << std::endl;
           std::cout << " UNIFORM LOCATION: " << location << std::endl;
       }
       return location;
}

void UniformManager::SetUniform4f(GLint& location, float r, float g, float b, float a) 
{
    DebugLog( glUniform4f(location, r, g, b, a));
}

void UniformManager::SetUniformMat4f(GLint& location, glm::mat4& matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void UniformManager::SetUniform1i(GLint& location, int i)
{
    glUniform1i(location, i);
}

//void UniformManager::SetUniform1i(ShaderSource& source, std::string& name, int i) 
//{
//    DebugLog(glUniform1i(source.uniformLocation[name], i));
//}
//
//void UniformManager::SetUniform1f(ShaderSource& source, std::string& name, float f) 
//{
//    DebugLog(glUniform1f(source.uniformLocation[name], f));
//}
