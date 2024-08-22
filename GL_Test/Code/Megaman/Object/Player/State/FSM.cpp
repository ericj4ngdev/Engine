#include "include.h"

FSM::FSM(CGameObject* l_gameObject) : CComponent("FSM", l_gameObject), m_CurrentState(nullptr)
{
	CCharacter* Character = dynamic_cast<CCharacter*>(gameObject);
	m_IdleState = new CStateIdle(Character);
	m_JumpState = new CStateJump(Character);
}

FSM::~FSM()
{
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
		m_CurrentState->Exit();
	}
	m_CurrentState = InNextState;
	InNextState->Enter();
}

void FSM::Update()
{
	if (m_CurrentState != nullptr)
	{
		m_CurrentState->Update();
	}
}
