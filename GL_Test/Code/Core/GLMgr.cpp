#include "include.h"

int GLMgr::g_screenWidth = 480;
int GLMgr::g_screenHeight = 480;

GLMgr::GLMgr()
{
    VAO = 0;
    VBO = 0;
    programID = 0;
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

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);     // 1. Vertex Array Object 바인딩

    programID = ShaderUtil::CreateProgram("VertexShader.txt", "FragmentShader.txt");
    
    DrawSquare();
    texture.LoadImage("Code/Asset/Image/Test.png");
    m_Texid = NULL;
    m_Texid = *texture.GetTexture();
}

void GLMgr::Update()
{
}

void GLMgr::Render()
{
    // 여기서 Scene의 Tick을 호출
    glClear(GL_COLOR_BUFFER_BIT);
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, m_Texid);

    glUseProgram(programID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, 4);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Double buffer
    glutSwapBuffers();   // 백버퍼와 프론트버퍼를 교환하여 화면에 그려진 결과를 표시
}

void GLMgr::DrawSquare()
{
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    
// ------------------------------
    glBindVertexArray(VAO);     // 1. Vertex Array Object 바인딩    

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}