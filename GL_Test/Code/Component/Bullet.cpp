#include "include.h"

COMPONENT_CONSTRUCTOR(Bullet) ,m_vDirection(vec2(0,0))
{
	m_speed = 500;
}

void Bullet::Init()
{
}

void Bullet::Update()
{
	// 칼 본인 위치 받아오기. 그런데 항상 0,0이다...
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	Movement();	
	// printf("Bullet (%f, %f)\n", m_curpos.x, m_curpos.y);
}

void Bullet::FinalUpdate()
{

}

void Bullet::Render()
{

}

void Bullet::Destroy()
{

}

Bullet::~Bullet()
{

}

void Bullet::Movement()
{
	m_curpos += m_vDirection * m_speed * fDT;
	gameObject->GetComponent<CAnimator>()->Play("Bullet", true);
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
