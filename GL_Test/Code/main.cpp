// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "include.h"


using namespace std;


int screenWidth = 480;
int screenHeight = 480;
GLuint programID;
GLuint VAO;
GLuint VBO;

float vertices[] = 
{
     // 위치              // 컬러
     -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
     -0.8f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
     -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,

     0.8f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f 
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    //create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgramID;

    GLint success;
    int InfoLogLength;

    #pragma region    // ========================= vertex ===========================
    //Read the vertex shader code from the file
    string VertexShaderCode;
    ifstream VertexShaderStream(vertex_file_path, ios::in);
    if (VertexShaderStream.is_open())
    {
        string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    //Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char VertexShaderErrorMessage[512];
        glGetShaderInfoLog(VertexShaderID, 512, NULL, VertexShaderErrorMessage);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }
#pragma endregion

    #pragma region// ========================= fragment ===========================
    //Read the fragment shader code from the file
    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path, ios::in);
    if (FragmentShaderStream.is_open())
    {
        string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    //Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    //Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char FragmentShaderErrorMessage[512];
        glGetShaderInfoLog(FragmentShaderID, 512, NULL, FragmentShaderErrorMessage);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }
#pragma endregion

    #pragma region// ========================= Link and check ===========================
    //Link the program
    fprintf(stdout, "Linking program\n");
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, VertexShaderID);
    glAttachShader(shaderProgramID, FragmentShaderID);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
    if (!success) 
    {        
        glGetProgramInfoLog(shaderProgramID, 512, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }
#pragma endregion

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return shaderProgramID;
}

void Update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 4. 오브젝트를 그립니다.
    glUseProgram(programID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Double buffer
    glutSwapBuffers();      // 백버퍼와 프론트버퍼를 교환하여 화면에 그려진 결과를 표시
}

void Triangle() 
{    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);        
    glBindVertexArray(VAO);     // 1. Vertex Array Object 바인딩

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 위치 정보
    GLuint posLoc = glGetAttribLocation(programID, "inPos");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(posLoc);

    // 색 정보
    GLuint colLoc = glGetAttribLocation(programID, "inCol");
    glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(colLoc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Init() 
{
    GLenum errorCode = glewInit();         //initilize the glew and check the errors.
    if (errorCode != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s' \n", glewGetErrorString(errorCode));
    }
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Simple OpenGL Window");

    Init();
    programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    
    Triangle();

    glutDisplayFunc(Update);
    glutMainLoop();

    glDeleteVertexArrays(1, &VAO);

    return 1;
}
