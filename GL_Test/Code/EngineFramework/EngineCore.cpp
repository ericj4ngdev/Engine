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
	CPathMgr::GetInstance()->Init();
	GLMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();
}

void EngineCore::Update()
{
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CCamera::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();	
	CCollisionMgr::GetInstance()->Update();
}

void EngineCore::Render()
{
	CTimeMgr::GetInstance()->Render();
	GLMgr::GetInstance()->Render();
	CSceneMgr::GetInstance()->Render();				// RenderCompo 갱신함

	glutSwapBuffers();
}

void EngineCore::Event()
{
	CEventMgr::GetInstance()->Update();
}
