#include "include.h"

COMPONENT_CONSTRUCTOR(FSM), m_CurrentState(nullptr)
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

void FSM::Init()
{

}

void FSM::Update()
{
	if (m_CurrentState != nullptr)
	{
		LOG("begin")
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
