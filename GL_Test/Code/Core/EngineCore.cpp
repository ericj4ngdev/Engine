#include "include.h"


EngineCore::EngineCore()
{

}

EngineCore::~EngineCore()
{
}

void EngineCore::Init()
{
	CTimeMgr::GetInstance()->Init();
	GLMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();
}

void EngineCore::Update()
{
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
}

void EngineCore::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);	//select the background color

	CSceneMgr::GetInstance()->Update();		// RenderCompo °»½ÅÇÔ

	glutSwapBuffers();
}
