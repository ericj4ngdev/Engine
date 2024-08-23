#include "include.h"


CStateHurt::CStateHurt(CMegaman* Character)	: CStateBase(Character, "Hurt") 
{
	m_fHitTimer = 0;
}

CStateHurt::~CStateHurt()
{
}

void CStateHurt::Enter()
{
	m_fHitTimer = 0;
}

void CStateHurt::Update()
{
	m_fHitTimer += fDT;
	if (m_fHitTimer < 0.5f)
	{
		if (m_Character->m_iDir == 1)
			m_Character->m_Animator->Play("Hit_Right", true);
		else
			m_Character->m_Animator->Play("Hit_Left", true);
	}
	else
	{		
		m_Character->SetbDamaged(false);
		m_fHitTimer = 0;
		m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
	}
}

void CStateHurt::Exit()
{
	m_fHitTimer = 0;
}
