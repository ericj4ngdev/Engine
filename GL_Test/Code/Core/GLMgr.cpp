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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      // png 투명화

}

void GLMgr::Resize(int width, int height)
{
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (height == 0)
        height = 1;
    float ratio = 1.0 * width / height;

    //좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //뷰포트를 창의 전체 크기로 설정합니다.
    glViewport(0, 0, width, height);

    //투시값을 설정합니다.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);

    //// 뷰포트 설정 (창의 크기에 따라 변경)
    //glViewport(0, 0, width, height);

    //// 프로젝션 행렬 설정
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    //// 원하는 프로젝션 설정을 여기에 추가 (예: 직교 투영)
    //// glOrtho(left, right, bottom, top, near, far);
    //glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);

    //// 모델뷰 행렬로 전환
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