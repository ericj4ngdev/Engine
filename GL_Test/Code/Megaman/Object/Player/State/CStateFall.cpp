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
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetIdleState());
    }
}

void CStateFall::Exit()
{
    m_Character->bOnAir = false;
}
