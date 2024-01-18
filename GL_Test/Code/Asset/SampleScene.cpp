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
	player->GetTransform()->m_scale = vec3{ 1.f,1.f,1.f };
	player->GetComponent<CRenderComponent>()->SetTexture("Code/Asset/Image/Test.png");

	

	AddObject(player);	
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
