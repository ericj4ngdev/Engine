#include "include.h"

void SampleScene::Init()
{
	// 안쓰임
}

void SampleScene::Enter()
{
	// player할당
	CGameObject* player = new CGameObject("Player");
	player->CreateComponent<CRenderComponent>();
	player->CreateComponent<ControllerComponent>();
	player->GetTransform()->m_scale = vec3{ 0.5f,1.f,1.f };
	player->GetComponent<CRenderComponent>()->SetTexture("Code/Asset/Image/player.png");
	AddObject(player);


	CGameObject* block = nullptr;
	for (int i = 0; i < 5; i++) 
	{
		block = new CGameObject("block");
		block->CreateComponent<CRenderComponent>();
		block->GetTransform()->m_position = vec3{ -0.5f + (float)i * 1.f ,-9.5f,0.1f };
		block->GetTransform()->m_scale = vec3{ 0.1f,0.1f,1.f };
		block->GetComponent<CRenderComponent>()->SetTexture("Code/Asset/Image/block.png");
		AddObject(block);
	}
	
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
