#include "include.h"

CCharacter::CCharacter(string name) : CGameObject(name), m_Controller(nullptr)
{
	bOnAir = false;
	m_bDamaged = false;
}

CCharacter::~CCharacter() = default;

void CCharacter::Init()
{
	// m_FSM->Initialize(m_CurrentState);
	CPlayerController* PC = CSceneMgr::GetInstance()->GetCurScene()->GetController();
	// Scene::Init에선 PC생성해서 push하지만 Character가 없음
	// PC가 null은 아닌데 GetController해도 null임 
	// 그래서 Character가 없음
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
	// 예시: C키가 눌렸다면 점프 상태로 전환
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

void CCharacter::TakeDamage(float damage, int dir)
{
	m_bDamaged = true;
}

