#include "include.h"

CStateRun::~CStateRun()
{
}

void CStateRun::Enter()
{

}

void CStateRun::Update()
{
    if (m_Character->m_iDir > 0)
    {
        m_Character->m_Animator->Play("Walk_Right", true);
    }
    else
    {
        m_Character->m_Animator->Play("Walk_Left", true);
    }

    // FallState
    if (!m_Character->m_Gravity->GetGround())
    {
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetFallState());
    }

    // 이동이 없으면 IdleState
    if (abs(m_Character->m_Rigidbody->GetVelocity().x) <= m_Character->m_MoveOffset)
    {
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetIdleState());
    }

    // C 키가 눌리고, 캐릭터가 공중에 있지 않을 때 점프 상태로 전환
    if (GetKeyDown(C) && !m_Character->bOnAir)
    {
        m_Character->Jump();
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetJumpState());
    }
}

void CStateRun::Exit()
{
}
