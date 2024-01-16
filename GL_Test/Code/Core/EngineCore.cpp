#include "include.h"


EngineCore::EngineCore()
{

}

EngineCore::~EngineCore()
{
}

void EngineCore::Init()
{
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();
}

void EngineCore::Update()
{
	CKeyMgr::GetInstance()->Update();
}
