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
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (height == 0)
        height = 1;
    double ratio = 1.0 * width / height;

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

}

void GLMgr::Update()
{
}

void GLMgr::Render()
{ 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);              // png 투명화
    glViewport(0, 0, GLMgr::g_screenWidth, GLMgr::g_screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLMgr::g_screenWidth, 0, GLMgr::g_screenHeight, 0.01, 1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 프레임마다 이전에 그려진 색상 버퍼와 깊이 버퍼를 초기화
    glClearColor(0.5, 0.5, 0.5, 1.0);	//select the background color
}