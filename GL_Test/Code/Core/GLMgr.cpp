#include "include.h"



GLMgr::GLMgr()
{
    
}
GLMgr::~GLMgr()
{
    
}

void GLMgr::Init()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %d\n", error);
    }
          
}

void GLMgr::Resize(int width, int height)
{
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (height == 0)
        height = 1;
    double ratio = 1.0 * width / height;

    //��ǥ�踦 �����ϱ� ���� �ʱ�ȭ�մϴ�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //����Ʈ�� â�� ��ü ũ��� �����մϴ�.
    glViewport(0, 0, width, height);

    //���ð��� �����մϴ�.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);

}

void GLMgr::Update()
{
}

void GLMgr::Render()
{ 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);              // png ����ȭ
    glViewport(0, 0, GLMgr::g_screenWidth, GLMgr::g_screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLMgr::g_screenWidth, 0, GLMgr::g_screenHeight, 0.01, 1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ӹ��� ������ �׷��� ���� ���ۿ� ���� ���۸� �ʱ�ȭ
    glClearColor(0.5, 0.5, 0.5, 1.0);	//select the background color
}