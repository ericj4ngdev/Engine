// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "include.h"
using namespace std;

void Update()
{
    EngineCore::GetInstance()->Update();
    EngineCore::GetInstance()->Render();    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(GLMgr::g_screenWidth, GLMgr::g_screenHeight);
    glutCreateWindow("Simple OpenGL Window");

    // 코어 초기화
    EngineCore::GetInstance()->Init();

    glutDisplayFunc(Update);
    glutMainLoop();    

    return 1;
}
