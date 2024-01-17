#include "include.h"

int GLMgr::g_screenWidth = 480;
int GLMgr::g_screenHeight = 480;

GLMgr::GLMgr()
{
    
}
GLMgr::~GLMgr()
{
    // glDeleteVertexArrays(1, &VAO);
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

    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glBindVertexArray(VAO);     // 1. Vertex Array Object ���ε�

    //programID = ShaderUtil::CreateProgram("VertexShader.txt", "FragmentShader.txt");
    
    /*texture.LoadImage("Code/Asset/Image/Test.png");
    m_Texid = NULL;
    m_Texid = *texture.GetTexture();*/
}

void GLMgr::Update()
{
}

void GLMgr::Render()
{
    // ���⼭ Scene�� Tick�� ȣ��
    // glClear(GL_COLOR_BUFFER_BIT);
    //// bind Texture
    //glBindTexture(GL_TEXTURE_2D, m_Texid);

    //glUseProgram(programID);
    //glBindVertexArray(VAO);
    //glDrawArrays(GL_QUADS, 0, 4);

    //Double buffer
    // glutSwapBuffers();   // ����ۿ� ����Ʈ���۸� ��ȯ�Ͽ� ȭ�鿡 �׷��� ����� ǥ��
}