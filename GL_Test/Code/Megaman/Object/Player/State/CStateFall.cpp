#include "include.h"

CStateFall::~CStateFall()
{
}

void CStateFall::Enter()
{
    m_Character->bOnAir = true;
}

void CStateFall::Update()
{
    if (m_Character->GetbDamaged())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetHurtState());
    }

    if (GetKeyDown(V))
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetAttackState());
        m_Character->Attack();
    }

    if (m_Character->m_iDir >= 0)
    {
        m_Character->m_Animator->Play("Jump_Right", true);
    }
    else
    {
        m_Character->m_Animator->Play("Jump_Left", true);
    }

    // 착지 하면 Idle로 전환
    if (m_Character->m_Gravity->GetGround())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
    }
}

void CStateFall::Exit()
{
    m_Character->bOnAir = false;
}
