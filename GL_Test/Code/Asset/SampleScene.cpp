#include "include.h"

void SampleScene::Init()
{
	// 안쓰임
}

void SampleScene::Enter()
{	
	{
		// player할당
		CPlayer* player = new CPlayer("Player");
		player->GetComponent<TransformComponent>()->SetPosition(vec2(100.f, 100.f));
		player->GetComponent<TransformComponent>()->SetScale(vec2(100.f, 200.f));
		AddObject(player, GROUP_TYPE::PLAYER);
	}

	{
		CZombie* zombie = nullptr;
		for (int i = 0; i < 5; i++)
		{
			zombie = new CZombie("Zombie"+i);
			zombie->GetComponent<TransformComponent>()->SetPosition(vec2( 300.f + (float)i * 100.f, 100.f));
			zombie->GetComponent<TransformComponent>()->SetScale(vec2{ 100.f, 200.f });
			AddObject(zombie, GROUP_TYPE::ENEMY);
		}
	}
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
