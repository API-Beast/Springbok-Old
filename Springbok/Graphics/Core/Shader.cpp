//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Shader.h"
#include <Springbok/Utils/Functions.h>

#include <fstream>

namespace
{
	std::string GetShaderLog(GLuint id)
	{
		int infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::string output(infoLogLength, ' ');
		glGetShaderInfoLog(id, infoLogLength, NULL, &output[0]);
		if(!output.empty())
		{
			if(output.back() == '\n') // Brrr I hate that last new line
				output = output.substr(0, output.size() - 1);
		}
		return output;
	}
};

Shader::Shader(Shader::ShaderType type)
{
	Handle = glCreateShader(type);
	Type = type;
}

Shader::Shader(const std::string& path, Shader::ShaderType type)
{
	std::ifstream file(path, std::ios::binary);
	std::string fileContent((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	
	Handle = glCreateShader(type);
	Type = type;
	loadSourceFromBuffer(fileContent);
	PrintGLError();
}

Shader::~Shader()
{
	glDeleteShader(Handle);
}

void Shader::loadSourceFromBuffer(const std::string& buffer)
{		
	const char* ptr = buffer.data();
	glShaderSource(Handle, 1, &ptr, NULL);
}

bool Shader::compile()
{
	glCompileShader(Handle);
	int success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		if(Type == Vertex)
			DebugLog("Vertex shader compilation failed:\n $", GetShaderLog(Handle));
		if(Type == Fragment)
			DebugLog("Fragment shader compilation failed:\n $", GetShaderLog(Handle));
	}
	return success;
}
