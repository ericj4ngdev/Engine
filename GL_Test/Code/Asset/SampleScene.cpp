#include "include.h"

void SampleScene::Init()
{
	// playerÇÒ´ç
	CGameObject* player = new CGameObject("Player");
	player->GetComponent<TransformComponent>()->m_position = vec3{ 0, 0, 0 };
	player->GetTransform()->m_scale = vec3{ 1.f,1.f,1.f };
}

void SampleScene::Enter()
{
}

void SampleScene::Exit()
{
}

void SampleScene::Update()
{
	
}

void SampleScene::Destroy()
{

}
