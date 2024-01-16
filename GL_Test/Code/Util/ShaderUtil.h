#pragma once

class ShaderUtil
{
public:
	unsigned int programID;
public:
	ShaderUtil();
	~ShaderUtil();
	void Use();
	// Uniform 유틸리티 함수들
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;


	static GLuint CreateProgram(const char* vertex_file_path, const char* fragment_file_path);
	static GLuint LoadShader(GLenum shaderType, const char* pfile_path);
	static void BindAttributeToShader();
};

