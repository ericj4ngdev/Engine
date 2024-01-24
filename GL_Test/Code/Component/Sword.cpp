#include "include.h"

COMPONENT_CONSTRUCTOR(Sword) ,m_vDirection(vec2(0,0))
{
	m_speed = 500;
}

void Sword::Init()
{
}

void Sword::Update()
{
	// 칼 본인 위치 받아오기. 그런데 항상 0,0이다...
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	Movement();
	printf("Sword (%f, %f)\n", m_curpos.x, m_curpos.y);
}

void Sword::FinalUpdate()
{

}

void Sword::Render()
{

}

void Sword::Destroy()
{

}

Sword::~Sword()
{

}

void Sword::Movement()
{
	m_curpos += m_vDirection * m_speed * fDT;

	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
