#pragma once

#include "CStateBase.h"
#include "CStateIdle.h"
#include "CStateJump.h"

class FSM : public CComponent
{
public:
    COMPONENT_DEFINE_CONSTRUCTOR(FSM)
    ~FSM(); 

    void Initialize(CStateBase* InStartingState);
    void TransitionTo(CStateBase* InNextState);
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;

    // ���� ��ü ������
    CStateIdle* GetIdleState() const { return m_IdleState; }
    CStateJump* GetJumpState() const { return m_JumpState; }

private:
    CStateBase* m_CurrentState;

    // ���� ��ü���� FSM�� ����
    CStateIdle* m_IdleState;
    CStateJump* m_JumpState;
};
