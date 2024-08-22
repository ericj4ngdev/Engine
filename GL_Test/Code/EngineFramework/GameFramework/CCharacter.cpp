#include "include.h"

CCharacter::CCharacter(string name) : CGameObject(name)
{
	Init();
}

CCharacter::~CCharacter() = default;

void CCharacter::Init()
{
	// GetPlayerController
	
	CPlayerController* PC = CSceneMgr::GetInstance()->GetCurScene()->GetController();
	if (PC)
	{
		PC->OnPossess(this);
	}
	else
	{
		cout << "CCharacter::Init() CPlayerController is null";
	}
}

void CCharacter::Update()
{
	// 예시: C키가 눌렸다면 점프 상태로 전환
	if (GetKeyDown(C) && !bOnAir)
	{
		Jump();
	}
}

void CCharacter::Possessedby(CPlayerController* InController)
{
	m_Controller = InController;
}

void CCharacter::UnPossesed()
{
	m_Controller = nullptr;
}

void CCharacter::Jump()
{
	bOnAir = true;
}

