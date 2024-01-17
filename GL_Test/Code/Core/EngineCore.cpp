#include "include.h"


EngineCore::EngineCore()
{

}

EngineCore::~EngineCore()
{
}

void EngineCore::Init()
{
	GLMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();
}

void EngineCore::Update()
{
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();
}

void EngineCore::Render()
{
	GLMgr::GetInstance()->Render();
}
