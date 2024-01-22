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

	// player할당
	CPlayer* player = new CPlayer("Player");
	player->GetComponent<TransformComponent>()->SetPosition(vec2(100.f, 100.f));
	player->GetComponent<TransformComponent>()->SetScale(vec2(50.f, 100.f));
	AddObject(player, GROUP_TYPE::PLAYER);

	CZombie* zombie = nullptr;
	for (int i = 0; i < 5; i++)
	{
		zombie = new CZombie("Zombie" + i);
		zombie->GetComponent<TransformComponent>()->SetPosition(vec2( 300.f + (float)i * 100.f, 100.f));
		zombie->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 100.f });
		AddObject(zombie, GROUP_TYPE::ENEMY);
	}

	CBlock* block = nullptr;
	for (int i = 0; i < 30; i++)
	{
		block = new CBlock("Block" + i);
		block->GetComponent<TransformComponent>()->SetPosition(vec2(25.f + (float)i * 50.f, 25.f));
		block->GetComponent<TransformComponent>()->SetScale(vec2{ 50.f, 50.f });
		AddObject(block, GROUP_TYPE::MAP);
	}

	


}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
