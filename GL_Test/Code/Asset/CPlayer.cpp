#include "include.h"

CPlayer::CPlayer(string name) : CGameObject(name)
{
	Init();
}

CPlayer::~CPlayer() = default;

void CPlayer::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\player.png";
	CreateComponent<CRenderComponent>();
	CreateComponent<ControllerComponent>();
	CreateComponent<CCollider>();
	CreateComponent<CRigidbody>();
	GetComponent<CRenderComponent>()->SetTexture("PlayerTex", strFilePath.c_str());
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	printf("Collide with %s\n", pOther->gameObject->GetName().c_str());
}

