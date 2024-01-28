#include "include.h"

COMPONENT_CONSTRUCTOR(CRigidbody), m_Mass(1.f)
	, m_fFricCoeff(100.f)
	, m_fMaxVelocity(200.0f, 600.0f)
{
	
}
void CRigidbody::Init()
{
}
void CRigidbody::Update()
{
}
void CRigidbody::FinalUpdate()
{
	// printf("m_vForce (%f, %f)\n", m_vForce.x, m_vForce.y);
	// 힘의 크기
	float fForce = m_vForce.Length();
	if (fForce != 0.f) 
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도 크기
		float m_fAccel = fForce / m_Mass;

		// 가속도
		// m_vAccel = m_vForce / m_Mass;  // 힘이 노멀벡터화되어서 이 식 쓰면 안됨
		m_vAccel = m_vForce * m_fAccel;		
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * fDT;

	if (!(m_vVelocity.Length() == 0)) 
	{
		// 마찰력
		vec2 vFircDir = -m_vVelocity;
		vFircDir.Normalize();

		vec2 vFriction = vFircDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰력이 본래 속도보다 큰 경우(반대로 가는 경우 방지) 
			m_vVelocity = vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한
	if (abs(m_vVelocity.x) > abs(m_fMaxVelocity.x))
	{
		// 최고 속도
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_fMaxVelocity.x);
	}

	if (abs(m_vVelocity.y) > abs(m_fMaxVelocity.y))
	{
		// 최고 속도
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_fMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = vec2(0.f, 0.f);

	// 가속도 초기화
	m_vAccel = vec2(0.f, 0.f);
	m_vAccelA = vec2(0.f, 0.f);
}

void CRigidbody::Render()
{

}

void CRigidbody::Destroy()
{

}

CRigidbody::~CRigidbody() 
{

}

void CRigidbody::Move()
{
	// 이동 속력
	m_speed = m_vVelocity.Length();
	
	if ( 0.f != m_speed)
	{
		// 이동 방향
		vec2 vDir = m_vVelocity;
		vDir.Normalize();

		vec2 vPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
		vPos += m_vVelocity * fDT;

		gameObject->GetComponent<TransformComponent>()->SetPosition(vPos);
	}
}
