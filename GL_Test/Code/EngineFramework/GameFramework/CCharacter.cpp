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
	// ����: CŰ�� ���ȴٸ� ���� ���·� ��ȯ
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

