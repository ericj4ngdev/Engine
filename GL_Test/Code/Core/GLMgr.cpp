#include "include.h"

int GLMgr::g_screenWidth = 480;
int GLMgr::g_screenHeight = 480;

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
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void GLMgr::Update()
{
}

void GLMgr::Render()
{
}