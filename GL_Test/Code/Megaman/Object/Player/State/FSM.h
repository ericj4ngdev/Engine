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

    // ���� ��ü ������
    CStateIdle* GetIdleState() const { return m_IdleState; }
    CStateJump* GetJumpState() const { return m_JumpState; }

private:
    CStateBase* m_CurrentState;

    // ���� ��ü���� FSM�� ����
    CStateIdle* m_IdleState;
    CStateJump* m_JumpState;
};
