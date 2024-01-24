#include "include.h"

CSword::CSword()
{
	Init();
}

CSword::CSword(string name) : CGameObject(name)
{
	Init();
}

CSword::~CSword() = default;

void CSword::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\block.png";
	CreateComponent<CRenderComponent>();
	CreateComponent<CCollider>();
	CreateComponent<Sword>();
	GetComponent<CRenderComponent>()->SetTexture("SwordTex", strFilePath.c_str());
}

void CSword::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (dynamic_cast<CZombie*>(pOtherObj))
	{
		DeleteObject(this);
	}
}
