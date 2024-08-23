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
    // C Ű�� ������, ĳ���Ͱ� ���߿� ���� ���� �� ���� ���·� ��ȯ
    if (GetKeyDown(C) && !m_Character->bOnAir)
    {
        m_Character->Jump();
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetJumpState());
    }

    if (GetKeyDown(V))
    {
        m_Character->Attack();
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetAttackState());
    }

    // ���� ������
    if (!m_Character->m_Gravity->GetGround())
    {
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetFallState());
    }

    // RunState
    if (abs(m_Character->m_Rigidbody->GetVelocity().x) > m_Character->m_MoveOffset)
    {
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetRunState());        
    }
}

void CStateIdle::Exit()
{
	
}
