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

	// CRabbit* enemy = nullptr;
	// string enemyName = "enemy";
	// enemy = new CRabbit(enemyName);
	// enemy->GetComponent<TransformComponent>()->SetPosition(vec2(400.f, 200.f));
	// enemy->GetComponent<TransformComponent>()->SetScale(vec2{ 75.f, 80.f });
	// enemy->GetComponent<CCollider>()->Init();
	// AddObject(enemy, GROUP_TYPE::ENEMY);

	/*for (int i = 0; i < 3; i++)
	{
		string enemyName = "enemy" + to_string(i);
		enemy = new CRabbit(enemyName);
		enemy->GetComponent<TransformComponent>()->SetPosition(vec2( 500.f + (float)i * 200.f, 200.f));
		enemy->GetComponent<TransformComponent>()->SetScale(vec2 { 75.f, 80.f });
		enemy->GetComponent<CCollider>()->Init();
		AddObject(enemy, GROUP_TYPE::ENEMY);
	}*/

	CEnemyProjectile* pro = new CEnemyProjectile();
	pro->SetPos(vec2(-350.f, 150.f));
	AddObject(pro, GROUP_TYPE::PROJ_ENEMY);

	CEnemySpawner* spot = new CEnemySpawner();
	spot->SetPos(vec2(600.f, 100.f));
	spot->SetEnemy(ENEMY::RABBIT);
	spot->GetComponent<CCollider>()->Init();
	AddObject(spot, GROUP_TYPE::SPAWNER);

	//string blockName = "Block" + to_string(1);
	//block = new CBlock(blockName);
	//block->GetComponent<TransformComponent>()->SetPosition(vec2(175.f, 25.f));	// 원래 y값 25
	//block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
	//block->GetComponent<CCollider>()->Init();
	//AddObject(block, GROUP_TYPE::MAP);
	
	CBlock* block = nullptr;
	{
		// boundary
		string blockName = "Block" + to_string(0);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(-70.f, 110.f)));
		block->SetScale(vec2{ 50.f, 2000.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(0);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 7.5f, 110.f)));
		block->SetScale(vec2{ 50.f * 16, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(1);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 17.3f, 160.f)));	// 원래 y값 25
		block->SetScale(vec2{ 50.f * 4, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		// 공중
		blockName = "Block" + to_string(2);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 7.75f, 250.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(3);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 22.0f, 110.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(4);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 27.0f, 160.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(5);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 36.9f, 210.f)));
		block->SetScale(vec2{ 50.f * 14.3, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(6);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 48.0f, 160.f)));
		block->SetScale(vec2{ 50.f * 8, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(7);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 63.3f, 110.f)));
		block->SetScale(vec2{ 50.f * 22.5, 50.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);

		blockName = "Block" + to_string(8);
		block = new CBlock(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 79.3f, 110.f)));
		block->SetScale(vec2{ 50.f * 7, 2000.f });
		block->GetComponent<CCollider>()->Init();
		AddObject(block, GROUP_TYPE::MAP);
	}
	

	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);


	ivec2 vResolution = ivec2(GLMgr::g_screenWidth, GLMgr::g_screenWidth);

	// CCamera::GetInstance()->SetLookAt(vResolution / 2.f);
}

void SampleScene::Update()
{
	CScene::Update();
	// 그룹 개수 확인해보기
	printf("%d\n", m_arrObj[(int)GROUP_TYPE::ENEMY].size());
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
