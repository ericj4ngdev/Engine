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
	// ���ӵ� ����
	gameObject->GetComponent<CRigidbody>()->SetAccelAlpha(vec2(0.f, -m_gravity));
	if (m_bGround == false) {
		// ���� ���ϰ� ����
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
