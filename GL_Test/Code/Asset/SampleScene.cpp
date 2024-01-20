#include "include.h"

void SampleScene::Init()
{
	// 안쓰임
}

void SampleScene::Enter()
{
	CTexture* pTex = new CTexture;

	//char* strFilePath += CPathMgr::GetInstance()->GetContentPath();
	//strFilePath = "Texture/player.png" ;
	{
		std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
		// player할당
		CGameObject* player = new CGameObject("Player");
		player->CreateComponent<CRenderComponent>();
		player->CreateComponent<ControllerComponent>();
		player->GetTransform()->m_scale = vec3{ 0.5f,1.f,1.f };
		strFilePath += "texture\\player.png";
		player->GetComponent<CRenderComponent>()->SetTexture(strFilePath.c_str());
		AddObject(player);
	}


	{
		std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
		strFilePath += "texture\\Zombie1.png";
		CGameObject* block = nullptr;
		for (int i = 0; i < 5; i++)
		{
			block = new CGameObject("block");
			block->CreateComponent<CRenderComponent>();
			block->GetTransform()->m_position = vec3{ -0.5f + (float)i * 1.f ,-9.5f,0.1f };
			block->GetTransform()->m_scale = vec3{ 0.1f,0.1f,1.f };
			block->GetComponent<CRenderComponent>()->SetTexture(strFilePath.c_str());
			AddObject(block);
		}
	}
}

void SampleScene::Exit()
{
}

void SampleScene::Destroy()
{

}
