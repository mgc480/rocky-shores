#include "Shader.h"

Shader::Shader(std::string source, GLenum type, std::string _shaderName){
	shaderName = _shaderName;
	try{
		compile(source, type);
	}catch(Defaults::Exception e){
		throw e;
	}
}

Shader::~Shader(void){
	glDeleteShader(shaderId);
	shaderId = 0;
	compiled = false;
}

GLuint Shader::getShaderId(void){
	if(compiled){
		return shaderId;
	}

	throw Defaults::Exception(Defaults::SHADER_ERROR, "the shader who's id was requested has not been compiled", __LINE__, __FILE__);
}

void Shader::compile(std::string source, GLenum type){
	try{
		compile(source, type, &shaderId, shaderName);
	}catch(Defaults::Exception e){
		throw e;
	}
	compiled = true;
}

void Shader::compile(std::string source, GLenum type, GLuint * shaderId){
	GLuint tempShader = 0;	//if the shader id is 0 later on there most have been an error

	//make sure the source actually contains something
	if(source == ""){
		throw Defaults::Exception(Defaults::INVALID_STRING, "the source given for the shader was invalid (it's blank )");
	}

	//create object and check if it was created
	tempShader = glCreateShader(type);
	if(tempShader == 0){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "could not create a shader object", __LINE__, __FILE__);
	}

	//set the source of the shader
	const char* code = source.c_str();
	glShaderSource(tempShader, 1, (const GLchar**)&code, NULL);

	//compile the shader and output this fact, also we need a stringstream because opengl is extra special
	std::ostringstream oss;
	oss << tempShader;
	Log::status("compiling shader with id: " + oss.str());
	oss.str("");
	oss.clear();
	glCompileShader(tempShader);

	//check for compilation errors
	GLint status;	//holds the compilation status
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &status);	//put the status in status, he he

	if(status == GL_FALSE){
		oss << tempShader;
		std::string message = "unable to compile shader with id: " + oss.str();	//the error that will be thrown
		oss.str("");
		oss.clear();

		std::string error = "";	//holds opengl error

		//get the error message from opengl (why opengl why does it have to be this way)
		GLint infoLogLength;
		glGetShaderiv(tempShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(tempShader, infoLogLength, NULL, strInfoLog);
		error += strInfoLog;
		delete[] strInfoLog;

		//free the memory being used to hold the shader
		glDeleteShader(tempShader);
		tempShader = 0;

		//throw a shader error with opengl's error message
		message += " opengl returned\"" + error + "\"";
		throw Defaults::Exception(Defaults::SHADER_ERROR, message, __LINE__, __FILE__);
	}

	//if it reached hear then it was probobaly succesfull
	oss.str("");
	oss.clear();
	oss << tempShader;
	Log::status("shader sucessfully compiled id: " + oss.str());

	*shaderId = tempShader;
}
