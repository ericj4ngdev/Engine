#include "include.h"


ShaderUtil::ShaderUtil()
{
}

ShaderUtil::~ShaderUtil()
{
}

void ShaderUtil::Use()
{
    programID = CreateProgram("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);
}

void ShaderUtil::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}
void ShaderUtil::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void ShaderUtil::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

GLuint ShaderUtil::CreateProgram(const char* vertex_file_path, const char* fragment_file_path)
{
    GLuint VertexShaderID = LoadShader(GL_VERTEX_SHADER, vertex_file_path);
    if (!VertexShaderID) { return 0;}

    GLuint FragmentShaderID = LoadShader(GL_FRAGMENT_SHADER, fragment_file_path);
    if (!FragmentShaderID) { return 0; }

#pragma region// ========================= Link and check ===========================
    GLint success;
    int InfoLogLength;
    GLuint programID = glCreateProgram();

    //Link the program
    fprintf(stdout, "Linking program\n");
    glAttachShader(programID, VertexShaderID);
    glAttachShader(programID, FragmentShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }
#pragma endregion

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

	return programID;
}

GLuint ShaderUtil::LoadShader(GLenum eShaderType, const char* pfile_path)
{
    //create the shaders
    GLuint shader = glCreateShader(eShaderType);
    GLint success = 0;

    //Read the vertex shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(pfile_path, std::ios::in);
    if (shaderStream.is_open())
    {
        std::string Line = "";
        while (getline(shaderStream, Line))
            shaderCode += "\n" + Line;
        shaderStream.close();
    }

    //Compile Vertex Shader
    printf("Compiling shader : %s\n", pfile_path);
    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shader, 1, &sourcePointer, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char ShaderErrorMessage[512];
        glGetShaderInfoLog(shader, 512, NULL, ShaderErrorMessage);
        fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
    }

	return shader;
}

// ¾ê¸¦ È£ÃâÇÏ¸é ±×·ÁÁü
void ShaderUtil::BindAttributeToShader()
{



}
