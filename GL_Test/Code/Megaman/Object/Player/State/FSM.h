#pragma once

class CStateBase;
class CStateIdle;
class CStateJump;
class CStateRun;
class CStateFall;
class CStateAttack;

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

    // 상태 객체 접근자
    CStateBase* GetCurrentState() const { return m_CurrentState; }
    CStateBase* GetPreviousState() const { return m_PrevState; }
    CStateIdle* GetIdleState() const { return m_IdleState; }
    CStateJump* GetJumpState() const { return m_JumpState; }
    CStateRun* GetRunState() const { return m_RunState; }
    CStateFall* GetFallState() const { return m_FallState; }
    CStateAttack* GetAttackState() const { return m_AttackState; }
private:
    CStateBase* m_CurrentState;
    CStateBase* m_PrevState;
    CStateIdle* m_IdleState;
    CStateJump* m_JumpState;
    CStateRun* m_RunState;
    CStateFall* m_FallState;
    CStateAttack* m_AttackState;
};
