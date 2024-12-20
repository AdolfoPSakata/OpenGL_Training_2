#pragma once

#include <Definitions.h>

#include <OpenGLDebugger.h>
#include <IndexBuffer.h>
#include <VertexArrayObject.h>

#include <iostream>
#include <array> 

#define SetUniform(x) (GLEW_GET_FUN(x))

class UniformManager
{
public:
	UniformManager();
	~UniformManager();

	GLint PreProcessUniforms(GLint& id, std::string uniformString);
	void SetUniform4f(GLint& location, float r, float g, float b, float a);
	void SetUniformMat4f(GLint& location, glm::mat4& matrix);
	void SetUniform1i(GLint& location, int i);
private:

	//void SetUniform1i(ShaderSource& source, std::string& name, int i) ;
	//void SetUniform1f(ShaderSource& source, std::string& name, float f) ;
};

