#include "include.h"

int GLMgr::g_screenWidth = 720;
int GLMgr::g_screenHeight = 720;

GLMgr::GLMgr()
{
    
}
GLMgr::~GLMgr()
{
    
}

void GLMgr::Init()
{
    GLenum errorCode = glewInit();         //initilize the glew and check the errors.
    if (errorCode != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s' \n", glewGetErrorString(errorCode));
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      // png ����ȭ

}

void GLMgr::Resize(int width, int height)
{
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (height == 0)
        height = 1;
    float ratio = 1.0 * width / height;

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

    //// ����Ʈ ���� (â�� ũ�⿡ ���� ����)
    //glViewport(0, 0, width, height);

    //// �������� ��� ����
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    //// ���ϴ� �������� ������ ���⿡ �߰� (��: ���� ����)
    //// glOrtho(left, right, bottom, top, near, far);
    //glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);

    //// �𵨺� ��ķ� ��ȯ
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

void GLMgr::Update()
{
}

void GLMgr::Render()
{
    Resize(GLMgr::g_screenWidth, GLMgr::g_screenHeight);
}