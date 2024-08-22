#include "include.h"

CStateJump::~CStateJump()
{
}

void CStateJump::Enter()
{
	
}

void CStateJump::Update()
{
    if (!m_Character->bOnAir)
    {
        m_Character->GetFSM()->TransitionTo(m_Character->GetFSM()->GetJumpState());
    }
}

void CStateJump::Exit()
{
}
