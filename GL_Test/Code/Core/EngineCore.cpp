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
	CSceneMgr::GetInstance()->Update();
}

void EngineCore::Render()
{

}
