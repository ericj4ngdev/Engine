#include "include.h"


void SStage01::Init()
{
	CScene::Init();
}

void SStage01::Enter()
{
	
	
}

void SStage01::Update()
{
	CScene::Update();
	if (GetKeyDown(ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void SStage01::FinalUpdate()
{
}

void SStage01::Render()
{
}

void SStage01::Exit()
{
	DeleteAll();
	// 그룹 설정 해제하기
	CCollisionMgr::GetInstance()->Reset();
}

void SStage01::Destroy()
{
}

SStage01::SStage01()
{
}

SStage01::~SStage01()
{
}
