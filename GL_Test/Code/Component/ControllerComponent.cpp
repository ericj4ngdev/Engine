#include "include.h"

COMPONENT_CONSTRUCTOR(ControllerComponent) 
{
	m_pos = { 0, 0 };
}


ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
}

void ControllerComponent::Tick()
{
	Control();
	
}

void ControllerComponent::Destroy()
{
}

void ControllerComponent::Control()
{	
	if (GetKeyHold(W))
	{
		m_pos.y += 1.f * fDT;
		printf("%f\n", m_pos.y);
	}
	if (GetKeyHold(A))
	{
		m_pos.x -= 1.f * fDT;
		printf("%f\n", m_pos.x);
	}
	if (GetKeyHold(S))
	{
		m_pos.y -= 1.f * fDT;
		printf("%f\n", m_pos.y);
	}
	if (GetKeyHold(D))
	{
		m_pos.x += 1.f * fDT;
		printf("%f\n", m_pos.x);
	}
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_pos.x, m_pos.y);
}
