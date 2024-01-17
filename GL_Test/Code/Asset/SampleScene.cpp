#include "include.h"

void SampleScene::Init()
{
	// playerÇÒ´ç
	CGameObject* player = new CGameObject("Player");
	player->GetComponent<Transform>()->m_position = vec3{ 0, 0, 0 };
	player->GetTransform()->m_scale = vec3{ 1.f,1.f,1.f };


}

void SampleScene::Enter()
{
}

void SampleScene::Exit()
{
}

void SampleScene::Tick(float elapsedTime)
{
	if (startTIme == 0) {
		startTIme = elapsedTime;
	}
	if (elapsedTime - startTIme > 3000) {
		startTIme = elapsedTime;
	}
}


void SampleScene::Update()
{
	// QueryPerformanceFrequency();
}

void SampleScene::Destroy()
{

}
