// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "include.h"
using namespace std;

bool InitInstance(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(GLMgr::g_screenWidth, GLMgr::g_screenHeight);
    glutCreateWindow("Simple OpenGL Window");

    return true;
}

void Update()
{
    EngineCore::GetInstance()->Update();
    EngineCore::GetInstance()->Render();
}

void OnIdle() 
{
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    if (!InitInstance(argc, argv)) return 0;
    
    // 코어 초기화
    EngineCore::GetInstance()->Init();
    
    glutDisplayFunc(Update);
    glutIdleFunc(OnIdle);
    glutMainLoop();    

    return 1;
}
