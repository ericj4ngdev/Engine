#include "include.h"


CZombie::CZombie(string name) : CGameObject(name)
{
	Init();
}

CZombie::~CZombie() = default;

void CZombie::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\Zombie1.png";
	CreateComponent<CRenderComponent>();
	GetComponent<CRenderComponent>()->SetTexture("Zombie1Tex", strFilePath.c_str());	
}

