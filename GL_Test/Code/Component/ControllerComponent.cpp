#include "include.h"

// CComponent�� �����ڸ� �ڽ� ������ �ʱ�ȭ�κ��� ȣ��
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
{
	m_speed = 100;
}


ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
	printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
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
	printf("Player (%f, %f)\r", m_curpos.x, m_curpos.y);
	// set(���� ��ġ + ��ȭ��)
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
