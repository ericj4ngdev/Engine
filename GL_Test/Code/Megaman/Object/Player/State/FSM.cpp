#include "include.h"

COMPONENT_CONSTRUCTOR(FSM), m_CurrentState(nullptr)
{
	CMegaman* Character = dynamic_cast<CMegaman*>(gameObject);
	m_IdleState = new CStateIdle(Character);
	m_JumpState = new CStateJump(Character);
	m_RunState = new CStateRun(Character);
	m_FallState = new CStateFall(Character);
	m_AttackState = new CStateAttack(Character);
}

FSM::~FSM()
{
}

void FSM::Init()
{
	Initialize(m_IdleState);
}

void FSM::Initialize(CStateBase* InStartingState)
{
	m_CurrentState = InStartingState;
	InStartingState->Enter();
}

void FSM::TransitionTo(CStateBase* InNextState)
{
	if (m_CurrentState)
	{
		m_PrevState = m_CurrentState;
		m_CurrentState->Exit();
	}
	m_CurrentState = InNextState;
	// LOG("m_CurrentState : %s", m_CurrentState->GetName())
	InNextState->Enter();
}

void FSM::Update()
{
	if (m_CurrentState != nullptr)
	{
		LOG("m_CurrentState : %s", m_CurrentState->GetName().c_str())
		m_CurrentState->Update();
	}
}

void FSM::FinalUpdate()
{
}

void FSM::Render()
{
}

void FSM::Destroy()
{
}
