#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include <vector>

using namespace std;

int screenWidth = 480;
int screenHeight = 480;
GLuint programID;
GLuint vertexBufferID[2];           // VBO, 위치, 색 이렇게 2개
GLuint VertexArrayID[2];            // VAO

vector <float> g_points;            // 점 정보
vector <float> g_colors;            // 색 정보

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    //create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // ========================= vertex ===========================
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

    //Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }

    // ========================= fragment ===========================
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
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    // ========================= Link and check ===========================
    //Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
    if(!Result)
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

// 그리기 함수
void renderScene(void)
{
    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //define the size of point and draw a point.
    if (g_points.size() > 0)
    {
        // 이 친구가 버택스 정보를 다 가지고 있다. 
        glBindVertexArray(VertexArrayID[0]);                // VAO 바인딩. 

        glDrawArrays(GL_LINES, 0, g_points.size() / 3);
        glDrawArrays(GL_POINTS, 0, g_points.size() / 3);
        glDrawArrays(GL_TRIANGLES, 0, g_points.size() / 3);
    }

    //Double buffer
    glutSwapBuffers();
}

void triangle() {
    glBindVertexArray(VertexArrayID[0]);                // VAO 바인딩

    // 위치 정보를 Ver
    GLuint posLoc = glGetAttribLocation(programID, "inPos");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[0]);
    glBufferData(GL_ARRAY_BUFFER, g_points.size() * sizeof(float), g_points.data(), GL_STATIC_DRAW);    // GPU에게 위치 데이터 전달
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));    // 데이터 할당
    glEnableVertexAttribArray(posLoc);

    // 색 정보
    GLuint colLoc = glGetAttribLocation(programID, "inCol");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[1]);
    glBufferData(GL_ARRAY_BUFFER, g_colors.size() * sizeof(float), g_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(colLoc);
}


void init()
{
    //initilize the glew and check the errors.
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
    }

    //select the background color
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);


    glGenVertexArrays(2, VertexArrayID);    // 1. Generate VAO
    glGenBuffers(2, vertexBufferID);        // VBO 생성
    glBindVertexArray(VertexArrayID[0]);    // VAO 바인딩
}


int main(int argc, char** argv)
{
    //init GLUT and create Window
    //initialize the GLUT
    glutInit(&argc, argv);
    //GLUT_DOUBLE enables double buffering (drawing to a background buffer while the other buffer is displayed)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Simple OpenGL Window");

    //call initization function
    init();

    // shader를 읽어오기
    programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);

    glutDisplayFunc(renderScene);

    //enter GLUT event processing cycle
    glutMainLoop();

    glDeleteVertexArrays(2, VertexArrayID);

    return 1;
}