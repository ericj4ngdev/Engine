#include "include.h"

CStateRun::~CStateRun()
{
}

void CStateRun::Enter()
{

}

void CStateRun::Update()
{
    if (m_Character->GetbDamaged())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetHurtState());
    }

    if (m_Character->m_iDir > 0)
    {
        m_Character->m_Animator->Play("Walk_Right", true);
    }
    else
    {
        m_Character->m_Animator->Play("Walk_Left", true);
    }

    if (GetKeyDown(V))
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetAttackState());
        m_Character->Attack();
    }

    // FallState
    if (!m_Character->m_Gravity->GetGround())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetFallState());
    }

    // 이동이 없으면 IdleState
    if (abs(m_Character->m_Rigidbody->GetVelocity().x) <= m_Character->m_MoveOffset)
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
    }

    // C 키가 눌리고, 캐릭터가 공중에 있지 않을 때 점프 상태로 전환
    if (GetKeyDown(C) && !m_Character->bOnAir)
    {
        m_Character->Jump();
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetJumpState());
    }
}

void CStateRun::Exit()
{
}
