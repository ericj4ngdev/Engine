#include "include.h"

COMPONENT_CONSTRUCTOR(CGravity), m_bGround(false)
{

}

void CGravity::Init()
{
}

void CGravity::Update()
{
}

void CGravity::FinalUpdate()
{
	// 가속도 제공
	gameObject->GetComponent<CRigidbody>()->SetAccelAlpha(vec2(0.f, -m_gravity));
	if (m_bGround == false) {
		// 점프 못하게 막기
	}
}

void CGravity::Render()
{
}

void CGravity::Destroy()
{
}

CGravity::~CGravity()
{
}

void CGravity::SetGround(bool b)
{
	m_bGround = b;
	if (m_bGround) 
	{
		vec2 vV = gameObject->GetComponent<CRigidbody>()->GetVelocity();
		gameObject->GetComponent<CRigidbody>()->SetVelocity(vec2(vV.x,0.f));
	}
}
