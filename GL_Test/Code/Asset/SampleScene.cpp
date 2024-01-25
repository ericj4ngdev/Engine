#include "include.h"

void SampleScene::Init()
{
	// 안쓰임
}

void SampleScene::Enter()
{
	CMap* map = new CMap("backgound");
	map->GetComponent<TransformComponent>()->SetPosition(vec2(3194.f, -7.5f));
	map->GetComponent<TransformComponent>()->SetScale(vec2(3500.f, 400.f) * 3.20f);
	AddObject(map, GROUP_TYPE::MAP);

	CPlayer* player = new CPlayer("Player");
	player->SetPos(vec2(175.f, 100.f));
	player->GetComponent<TransformComponent>()->SetScale(vec2(50.f, 100.f));
	player->GetComponent<CCollider>()->Init();
	AddObject(player, GROUP_TYPE::PLAYER);
	


	CCamera::GetInstance()->SetTarget(player);

	CZombie* zombie = nullptr;
	for (int i = 0; i < 5; i++)
	{
		string zombieName = "Zombie" + to_string(i);
		zombie = new CZombie(zombieName);
		zombie->GetComponent<TransformComponent>()->SetPosition(vec2( 300.f + (float)i * 100.f, 100.f));
		zombie->GetComponent<TransformComponent>()->SetScale(vec2 { 50.f, 100.f });
		zombie->GetComponent<CCollider>()->Init();
		AddObject(zombie, GROUP_TYPE::ENEMY);
	}

	CBlock* block = nullptr;
	for (int i = 0; i < 30; i++)
	{
		string blockName = "Block" + to_string(i);
		block = new CBlock(blockName);
		block->GetComponent<TransformComponent>()->SetPosition(vec2(25.f + (float)i * 50.f, 25.f));	// 원래 y값 25
		block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);
	}

	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);

	ivec2 vResolution = ivec2(GLMgr::g_screenWidth, GLMgr::g_screenWidth);

	// CCamera::GetInstance()->SetLookAt(vResolution / 2.f);
}

void SampleScene::Update()
{
	CScene::Update();
	if (GetKeyDown(ENTER)) 
	{
		ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void SampleScene::Exit()
{
	DeleteAll();
	// 그룹 설정 해제하기
	CCollisionMgr::GetInstance()->Reset();
}

void SampleScene::Destroy()
{

}

SampleScene::SampleScene()
{
}

SampleScene::~SampleScene()
{
}
