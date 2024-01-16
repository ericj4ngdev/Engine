#include "include.h"

int GLMgr::g_screenWidth = 480;
int GLMgr::g_screenHeight = 480;

GLMgr::GLMgr()
{
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint programID = 0;
}
GLMgr::~GLMgr()
{
    glDeleteVertexArrays(1, &VAO);
}

void GLMgr::Init()
{
    GLenum errorCode = glewInit();         //initilize the glew and check the errors.
    if (errorCode != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s' \n", glewGetErrorString(errorCode));
    }
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    programID = ShaderUtil::CreateProgram("VertexShader.txt", "FragmentShader.txt");
    Triangle();
}

void GLMgr::Update()
{
}

void GLMgr::Render()
{
    // 여기서 Scene의 Tick을 호출
    glClear(GL_COLOR_BUFFER_BIT);

    // 4. 오브젝트를 그립니다.
    glUseProgram(programID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 6);       // 사각형은 Line Loop로 그리기

    //Double buffer
    glutSwapBuffers();      // 백버퍼와 프론트버퍼를 교환하여 화면에 그려진 결과를 표시

}

void GLMgr::Triangle()
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