#include "include.h"

void SampleScene::Init()
{
	// 안쓰임
}

void SampleScene::Enter()
{
	CMap* map = new CMap("backgound");
	vec2 offset = vec2(6000.f, -1600.0f);
	map->SetPos(offset + vec2(0,0));
	map->SetScale(vec2(4098.f, 1282.f) * 3.20f);
	AddObject(map, GROUP_TYPE::MAP);

	CPlayer* player = new CPlayer("Player");
	player->SetPos(vec2(-450.f, 100.f));
	player->GetComponent<TransformComponent>()->SetScale(vec2(75.f, 75.f));
	player->GetComponent<CCollider>()->Init();
	AddObject(player, GROUP_TYPE::PLAYER);

	CEnemy* enemy = nullptr;
	for (int i = 0; i < 5; i++)
	{
		string enemyName = "enemy" + to_string(i);
		enemy = new CEnemy(enemyName);
		enemy->GetComponent<TransformComponent>()->SetPosition(vec2( 500.f + (float)i * 100.f, 500.f));
		enemy->GetComponent<TransformComponent>()->SetScale(vec2 { 75.f, 80.f });
		enemy->GetComponent<CCollider>()->Init();
		AddObject(enemy, GROUP_TYPE::ENEMY);
	}

	CBlock* block = nullptr;

	//string blockName = "Block" + to_string(1);
	//block = new CBlock(blockName);
	//block->GetComponent<TransformComponent>()->SetPosition(vec2(175.f, 25.f));	// 원래 y값 25
	//block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
	//block->GetComponent<CCollider>()->Init();
	//AddObject(block, GROUP_TYPE::MAP);

	string blockName = "Block" + to_string(0);
	block = new CBlock(blockName);
	block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300) 
				+ vec2(50.f * 7.25, 110.f)));
	block->SetScale(vec2{ 50.f * 16, 50.f });
	block->GetComponent<CCollider>()->Init();
	AddObject(block, GROUP_TYPE::MAP);

	blockName = "Block" + to_string(1);
	block = new CBlock(blockName);
	block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
				+ vec2(865.f, 160.f)));	// 원래 y값 25
	block->SetScale(vec2{ 50.f * 4, 50.f });
	block->GetComponent<CCollider>()->Init();
	AddObject(block, GROUP_TYPE::MAP);
	
	blockName = "Block" + to_string(2);
	block = new CBlock(blockName);
	block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
				+ vec2(50.f * 7.75f, 240.f)));
	block->SetScale(vec2{ 50.f * 5, 50.f });
	block->GetComponent<CCollider>()->Init();
	AddObject(block, GROUP_TYPE::MAP);

	blockName = "Block" + to_string(3);
	block = new CBlock(blockName);
	block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
				+ vec2(3500, 240.f)));
	block->SetScale(vec2{ 50.f * 100, 50.f });
	block->GetComponent<CCollider>()->Init();
	AddObject(block, GROUP_TYPE::MAP);

	//for (int i = 0; i < 5; i++)
	//{
	//	string blockName = "Block" + to_string(i);
	//	block = new CBlock(blockName);
	//	block->GetComponent<TransformComponent>()->SetPosition(vec2(25.f + (float)i * 50.f, 25.f));	// 원래 y값 25
	//	block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
	//	block->GetComponent<CCollider>()->Init();
	//	AddObject(block, GROUP_TYPE::MAP);
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	string blockName = "Block" + to_string(i + 5);
	//	block = new CBlock(blockName);
	//	block->GetComponent<TransformComponent>()->SetPosition(vec2(250.f + (float)i * 50.f, 125.f));	// 원래 y값 25
	//	block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
	//	block->GetComponent<CCollider>()->Init();
	//	AddObject(block, GROUP_TYPE::MAP);
	//}
	//for (int i = 0; i < 7; i++)
	//{
	//	string blockName = "Block" + to_string(i + 5);
	//	block = new CBlock(blockName);
	//	block->GetComponent<TransformComponent>()->SetPosition(vec2(500.f + (float)i * 50.f, 250.f));	// 원래 y값 25
	//	block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
	//	block->GetComponent<CCollider>()->Init();
	//	AddObject(block, GROUP_TYPE::MAP);
	//}

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
	// if (GetKeyDown(ENTER)) ChangeScene(SCENE_TYPE::STAGE_01);
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
