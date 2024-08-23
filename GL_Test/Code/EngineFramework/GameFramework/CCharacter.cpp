#include "include.h"

CCharacter::CCharacter(string name) : CGameObject(name)
{
	bOnAir = false;
}

CCharacter::~CCharacter() = default;

void CCharacter::Init()
{
	// m_FSM->Initialize(m_CurrentState);
	CPlayerController* PC = CSceneMgr::GetInstance()->GetCurScene()->GetController();
	if (PC)
	{
		PC->OnPossess(this);
	}
	else
	{
		cout << "CCharacter::Init() CPlayerController is null";
	}
	CGameObject::Init();
}

void CCharacter::Update()
{
	CGameObject::Update();
	// ����: CŰ�� ���ȴٸ� ���� ���·� ��ȯ
	// if (GetKeyDown(C) && !bOnAir)
	// {
	// 	Jump();
	// }
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
	LOG("%d", bOnAir)
	bOnAir = true;
	LOG("%d", bOnAir)
}

