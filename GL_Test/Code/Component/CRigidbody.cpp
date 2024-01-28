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
	// ���� ũ��
	float fForce = m_vForce.Length();
	if (fForce != 0.f) 
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ� ũ��
		float m_fAccel = fForce / m_Mass;

		// ���ӵ�
		// m_vAccel = m_vForce / m_Mass;  // ���� ��ֺ���ȭ�Ǿ �� �� ���� �ȵ�
		m_vAccel = m_vForce * m_fAccel;		
	}

	// �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	// �ӵ�
	m_vVelocity += m_vAccel * fDT;

	if (!(m_vVelocity.Length() == 0)) 
	{
		// ������
		vec2 vFircDir = -m_vVelocity;
		vFircDir.Normalize();

		vec2 vFriction = vFircDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// �������� ���� �ӵ����� ū ���(�ݴ�� ���� ��� ����) 
			m_vVelocity = vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ����
	if (abs(m_vVelocity.x) > abs(m_fMaxVelocity.x))
	{
		// �ְ� �ӵ�
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_fMaxVelocity.x);
	}

	if (abs(m_vVelocity.y) > abs(m_fMaxVelocity.y))
	{
		// �ְ� �ӵ�
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_fMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = vec2(0.f, 0.f);

	// ���ӵ� �ʱ�ȭ
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
	// �̵� �ӷ�
	m_speed = m_vVelocity.Length();
	
	if ( 0.f != m_speed)
	{
		// �̵� ����
		vec2 vDir = m_vVelocity;
		vDir.Normalize();

		vec2 vPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
		vPos += m_vVelocity * fDT;

		gameObject->GetComponent<TransformComponent>()->SetPosition(vPos);
	}
}
