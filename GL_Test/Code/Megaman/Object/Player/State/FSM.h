#pragma once
#include "CStateBase.h"
#include "CStateIdle.h"
#include "CStateJump.h"

class FSM : public CComponent
{
public:
    FSM(CGameObject* l_gameObject);
    ~FSM(); 

    void Initialize(CStateBase* InStartingState);
    void TransitionTo(CStateBase* InNextState);
    void Update();

    // 상태 객체 접근자
    CStateIdle* GetIdleState() const { return m_IdleState; }
    CStateJump* GetJumpState() const { return m_JumpState; }

private:
    CStateBase* m_CurrentState;

    // 상태 객체들을 FSM이 관리
    CStateIdle* m_IdleState;
    CStateJump* m_JumpState;
};
