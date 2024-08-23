#include "include.h"

CStateJump::~CStateJump()
{
}

void CStateJump::Enter()
{
    m_Character->bOnAir = true;
}

void CStateJump::Update()
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

    // �����ϱ� ������ ��
    if (m_Character->m_Rigidbody->GetVelocity().y < 0)
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetFallState());
    }

    // �����ϸ� Idle
    if (m_Character->bOnAir)
    {
        if (m_Character->m_Rigidbody->GetVelocity().y >= 0 && m_Character->m_Gravity->GetGround())
        {
            m_Character->bOnAir = false;
            m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
        }
    }
}

void CStateJump::Exit()
{
    // �����ϴ� ������ m_Character->bOnAir = false; ó����    
}
