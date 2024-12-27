#include "include.h"

void SampleScene::Enter()
{	
	auto map = std::make_unique<CMap>("backgound");
	vec2 offset = vec2(6000.f, -1600.0f);
	map->SetPos(offset + vec2(0,0));
	map->SetScale(vec2(4098.f, 1282.f) * 3.20f);
	AddObject(move(map), GROUP_TYPE::MAP);

	auto player = std::make_unique<CMegaman>("Player");
	player->SetPos(vec2(-300.f, 100.f));
	player->GetComponent<TransformComponent>()->SetScale(vec2(75.f, 75.f));
	// player->GetComponent<CCollider>()->Init();
	AddObject(move(player), GROUP_TYPE::PLAYER);

	/*CEnemySpawner* spot = nullptr;
	{
		string str_spotName = "Spot" + to_string(0);
		spot = new CEnemySpawner(str_spotName);
		spot->SetPos(vec2(600.f, 0.f));
		spot->SetEnemy(ENEMY::BAT);
		AddObject(spot, GROUP_TYPE::SPAWNER);

		str_spotName = "Spot" + to_string(1);
		spot = new CEnemySpawner(str_spotName);
		spot->SetPos(vec2(1000.f, 100.f));
		spot->SetEnemy(ENEMY::RABBIT);
		AddObject(spot, GROUP_TYPE::SPAWNER);
	}*/
	
	unique_ptr<CBlock> block = nullptr;
	{
		// boundary
		string blockName = "Block" + to_string(0);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(-70.f, 110.f)));
		block->SetScale(vec2{ 50.f, 2000.f });
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(0);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 7.5f, 110.f)));
		block->SetScale(vec2{ 50.f * 16, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(1);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 17.3f, 160.f)));	// 원래 y값 25
		block->SetScale(vec2{ 50.f * 4, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		// 공중
		blockName = "Block" + to_string(2);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 7.75f, 250.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(3);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 22.0f, 110.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(4);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 27.0f, 160.f)));
		block->SetScale(vec2{ 50.f * 5, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(5);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 36.9f, 210.f)));
		block->SetScale(vec2{ 50.f * 14.3, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(6);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 48.0f, 160.f)));
		block->SetScale(vec2{ 50.f * 8, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(7);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 63.3f, 110.f)));
		block->SetScale(vec2{ 50.f * 22.5, 50.f });		
		AddObject(move(block), GROUP_TYPE::MAP);

		blockName = "Block" + to_string(8);
		block = std::make_unique<CBlock>(blockName);
		block->SetPos(vec2(vec2(offset.x - 6500, offset.y + 1300)
			+ vec2(50.f * 79.3f, 110.f)));
		block->SetScale(vec2{ 50.f * 7, 2000.f });		
		AddObject(move(block), GROUP_TYPE::MAP);
	}
	

	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MAP, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);


	ivec2 vResolution = ivec2(GLMgr::g_screenWidth, GLMgr::g_screenWidth);

	// CCamera::GetInstance()->SetLookAt(vResolution / 2.f);
}

void SampleScene::Init()
{
	// 모든 객체 초기화
	CScene::Init();
}

void SampleScene::Update()
{
	CScene::Update();
	// 그룹 개수 확인해보기
	// printf("%d\n", m_arrObj[(int)GROUP_TYPE::ENEMY].size());
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
