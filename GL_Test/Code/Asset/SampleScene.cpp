#include "include.h"

void SampleScene::Init()
{
	// �Ⱦ���
}

void SampleScene::Enter()
{
	// player�Ҵ�
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
