#include "include.h"


void SStage01::Init()
{
}

void SStage01::Enter()
{
	CMap* map = new CMap("backgound");
	map->GetComponent<TransformComponent>()->SetPosition(vec2(3194.f, -7.5f));
	map->GetComponent<TransformComponent>()->SetScale(vec2(3500.f, 400.f) * 3.20f);
	AddObject(map, GROUP_TYPE::MAP);
	
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
