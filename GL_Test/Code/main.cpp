// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "include.h"
using namespace std;

bool InitInstance(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);
    glutInitWindowSize(GLMgr::g_screenWidth, GLMgr::g_screenHeight);
    glutCreateWindow("Simple OpenGL Window");

    return true;
}

void Init() {
    EngineCore::GetInstance()->Init();  // 코어 초기화
}

void Tick()
{
    EngineCore::GetInstance()->Update();
    EngineCore::GetInstance()->FinalUpdate();
    EngineCore::GetInstance()->Render();
}

void OnIdle() 
{
    GLMgr::g_screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    GLMgr::g_screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Tick();
    // glutPostRedisplay();
}

int GLMgr::g_screenWidth = 720;
int GLMgr::g_screenHeight = 720;

int main(int argc, char** argv)
{
    // 메모리 누수 체크
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(1012);

    if (!InitInstance(argc, argv)) return 0;
    
    Init();    
    glutDisplayFunc(Tick);
    glutIdleFunc(OnIdle);
    glutMainLoop();    

    return 0;
}
