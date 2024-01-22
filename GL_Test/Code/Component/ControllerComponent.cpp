#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
{
	m_speed = 100;
}


ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
}

void ControllerComponent::Update()
{
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	Control();	
}

void ControllerComponent::FinalUpdate()
{
}

void ControllerComponent::Render()
{
}

void ControllerComponent::Destroy()
{
}

void ControllerComponent::Control()
{
	if (GetKeyHold(W))
	{		
		m_curpos.y += m_speed * fDT;
	}
	if (GetKeyHold(A))
	{
		m_curpos.x -= m_speed * fDT;
	}
	if (GetKeyHold(S))
	{
		m_curpos.y -= m_speed * fDT;
	}
	if (GetKeyHold(D))
	{
		m_curpos.x += m_speed * fDT;
	}
	printf("\x1B[H");
	printf("\x1B[B");
	printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	// set(현재 위치 + 변화량)
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
