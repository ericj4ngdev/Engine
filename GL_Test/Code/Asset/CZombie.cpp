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
	CreateComponent<CCollider>();
	// CreateComponent<Zombie>();
	GetComponent<CRenderComponent>()->SetTexture("Zombie1Tex", strFilePath.c_str());	
}

void CZombie::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (dynamic_cast<CSword*>(pOtherObj))
	{
		DeleteObject(this);
	}
}
