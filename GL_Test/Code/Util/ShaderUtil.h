#pragma once

class ShaderUtil
{
public:
	ShaderUtil();
	~ShaderUtil();

	static GLuint CreateProgram(const char* vertex_file_path, const char* fragment_file_path);
	static GLuint LoadShader(GLenum shaderType, const char* pfile_path);
};

