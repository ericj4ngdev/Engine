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
	CSceneMgr::GetInstance()->Update();		// RenderCompo 갱신함
}

void EngineCore::FinalUpdate() 
{
	CSceneMgr::GetInstance()->FinalUpdate();	
}

void EngineCore::Render()
{
	GLMgr::GetInstance()->Render();
	CSceneMgr::GetInstance()->Render();		// RenderCompo 갱신함

	glutSwapBuffers();
}
