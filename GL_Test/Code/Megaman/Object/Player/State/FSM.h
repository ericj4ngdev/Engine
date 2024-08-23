#pragma once

class CStateBase;
class CStateIdle;
class CStateJump;
class CStateRun;
class CStateFall;

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
    CStateIdle* GetIdleState() const { return m_IdleState; }
    CStateJump* GetJumpState() const { return m_JumpState; }
    CStateRun* GetRunState() const { return m_RunState; }
    CStateFall* GetFallState() const { return m_FallState; }
private:
    CStateBase* m_CurrentState;
    CStateIdle* m_IdleState;
    CStateJump* m_JumpState;
    CStateRun* m_RunState;
    CStateFall* m_FallState;
};
