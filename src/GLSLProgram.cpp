#include "GLSLProgram.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::string;

GLSLProgram::GLSLProgram()
{
	handle = 0;
	linked = false;
}

GLSLProgram::~GLSLProgram()
{
	if (handle == 0)
		return;

	GLint numShaders = 0;
	gl::GetProgramiv(handle, gl::ATTACHED_SHADERS, &numShaders);

	GLuint* shaderNames = new GLuint[numShaders];
	gl::GetAttachedShaders(handle, numShaders, NULL, shaderNames);

	for (int i = 0; i < numShaders; i++)
		gl::DeleteShader(shaderNames[i]);

	gl::DeleteProgram(handle);
	delete[] shaderNames;
}

void GLSLProgram::start()
{
	gl::UseProgram(handle);
}

void GLSLProgram::stop()
{
	gl::UseProgram(0);
}

void GLSLProgram::attach(fs::path pathToFile)
{
	// file existence check
	if (!fs::exists(pathToFile))
	{
		throw GLSLProgramException("The file path \'" + pathToFile.string() + "\' is incorrect.");
	}
	// file extension description check
	string ext = pathToFile.extension().string();
	if (GLS::ShaderFileExtension.find(ext) == GLS::ShaderFileExtension.end())
	{
		throw GLSLProgramException("The file extension \'" + ext + "\' is incorrect.");
	}

	GLS::ShaderType type = GLS::ShaderFileExtension.at(ext);

	if (handle == 0)
	{
		handle = gl::CreateProgram();
		if (handle == 0)
			throw GLSLProgramException("Unable to create shader program \'" + pathToFile.string() + "\'.");
	}

	ifstream inFile(pathToFile.string(), std::ios::in);
	if (!inFile)
	{
		throw GLSLProgramException("Unable to open: \'" + pathToFile.string() + "\'.");
	}
	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();

	attach(code.str().c_str(), type, pathToFile.string().c_str());
}

void GLSLProgram::attach(const char* source, GLS::ShaderType type, const char* descriptor)
{
	if (handle == 0)
	{
		handle = gl::CreateProgram();
		if (handle == 0)
			throw GLSLProgramException(string("Unable to create shader program \'") + descriptor + "\'.");
	}

	GLuint shaderHandle = gl::CreateShader(GLS::ShaderTypeHash.at(type));

	gl::ShaderSource(shaderHandle, 1, &source, NULL);
	gl::CompileShader(shaderHandle);

	int result;
	gl::GetShaderiv(shaderHandle, gl::COMPILE_STATUS, &result);

	if (result == gl::FALSE_)
	{
		int length = 0;
		string logString;
		gl::GetShaderiv(shaderHandle, gl::INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			char* c_log = new char[length];
			int written = 0;
			gl::GetShaderInfoLog(shaderHandle, length, &written, c_log);
			logString = c_log;
			delete[] c_log;
		}
		string msg;
		if (descriptor)
			msg = string(descriptor) + ": shader compliation failed.\n";
		else
			msg = "Shader compilation failed.\n";

		msg += logString;
		gl::DeleteShader(shaderHandle);
		throw GLSLProgramException(msg);
	}

	gl::AttachShader(handle, shaderHandle);
}

void GLSLProgram::link()
{
	if (linked)
		return;
	if (handle <= 0)
		throw GLSLProgramException("Program has not been compiled.");

	gl::LinkProgram(handle);

	int result = 0;
	gl::GetProgramiv(handle, gl::LINK_STATUS, &result);

	if (result == gl::FALSE_)
	{
		int length = 0;
		string logString;

		gl::GetProgramiv(handle, gl::INFO_LOG_LENGTH, &length);

		if (length > 0)
		{
			char* c_log = new char[length];
			int written = 0;
			gl::GetProgramInfoLog(handle, length, &written, c_log);
			logString = c_log;
			delete[] c_log;
		}
		throw GLSLProgramException(string("Program link failed:\n") + logString);
	}

	linked = true;
}

GLint GLSLProgram::getHandle()
{
	return handle;
}

GLboolean GLSLProgram::isLinked()
{
	return linked;
}

void GLSLProgram::addUniformLocation(std::string name)
{
	if (uniforms.find(name) == uniforms.end())
	{
		GLint uniLocation = gl::GetUniformLocation(handle, name.c_str());
		if (uniLocation == -1)
			throw GLSLProgramException(string(name + " does not correspond to an active uniform variable."));
		uniforms[name] = uniLocation;
	}
}

void GLSLProgram::setUniform(std::string name, int value)
{
	gl::Uniform1i(uniforms[name], value);
}

void GLSLProgram::setUniform(std::string name, float value)
{
	gl::Uniform1f(uniforms[name], value);
}

void GLSLProgram::setUniform(std::string name, bool value)
{
	gl::Uniform1i(uniforms[name], value);
}

void GLSLProgram::setUniform(std::string name, float x, float y)
{
	gl::Uniform2f(uniforms[name], x, y);
}

void GLSLProgram::setUniform(std::string name, float x, float y, float z)
{
	gl::Uniform3f(uniforms[name], x, y, z);
}

void GLSLProgram::setUniform(std::string name, float x, float y, float z, float w)
{
	gl::Uniform4f(uniforms[name], x, y, z, w);
}
