#include "include.h"

void SampleScene::Init()
{
	// �Ⱦ���
}

void SampleScene::Enter()
{
	// player�Ҵ�
	CGameObject* player = new CGameObject("Player");
	player->GetComponent<TransformComponent>()->m_position = vec3{ 0, 0, 0 };
	player->GetTransform()->m_scale = vec3{ 1.f,1.f,1.f };
	player->CreateComponent<CRenderComponent>();
	player->GetComponent<CRenderComponent>()->SetTexture("Code/Asset/Image/Test.png");
	
	AddObject(player);	
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
