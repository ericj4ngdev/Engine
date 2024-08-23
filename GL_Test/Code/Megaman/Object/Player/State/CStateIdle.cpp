#include "include.h"

CStateIdle::~CStateIdle()
{
}

void CStateIdle::Enter()
{
    if (m_Character->m_iDir >= 0)
    {
        m_Character->m_Animator->Play("Idle_Right", true);
    }
    else
    {
        m_Character->m_Animator->Play("Idle_Left", true);
    }
}

void CStateIdle::Update()
{
    if (m_Character->GetbDamaged())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetHurtState());
    }
    // C 키가 눌리고, 캐릭터가 공중에 있지 않을 때 점프 상태로 전환
    if (GetKeyDown(C) && !m_Character->bOnAir)
    {
        m_Character->Jump();
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetJumpState());
    }

    if (GetKeyDown(V))
    {
        m_Character->Attack();
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetAttackState());
    }

    // 땅이 없으면
    if (!m_Character->m_Gravity->GetGround())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetFallState());
    }

    // RunState
    if (abs(m_Character->m_Rigidbody->GetVelocity().x) > m_Character->m_MoveOffset)
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetRunState());
    }
}

void CStateIdle::Exit()
{
	
}
