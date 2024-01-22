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
		player->GetComponent<TransformComponent>()->SetPosition(vec2(-1.f, -1.f));
		player->GetComponent<TransformComponent>()->SetScale(vec2(0.5f, 1.f));
		AddObject(player);
	}

	{
		CZombie* zombie = nullptr;
		for (int i = 0; i < 5; i++)
		{
			zombie = new CZombie("Zombie"+i);
			zombie->GetComponent<TransformComponent>()->SetPosition(vec2(- 0.5f + (float)i * 1.f, -2.f));
			zombie->GetComponent<TransformComponent>()->SetScale(vec2{ 0.1f,0.2f });
			AddObject(zombie);
		}
	}
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
