#include "include.h"

COMPONENT_CONSTRUCTOR(CRigidbody), m_Mass(1.f)
	, m_fFricCoeff(100.f)
	, m_fMaxSpeed(100.0f)
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
	printf("m_vForce (%f, %f)\n", m_vForce.x, m_vForce.y);
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

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}

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
	if (m_vVelocity.Length() > m_fMaxSpeed)
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}


	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = vec2(0.f, 0.f);
}
void CRigidbody::Render()
{
}
void CRigidbody::Destroy()
{
}
CRigidbody::~CRigidbody() {

}

void CRigidbody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();
	if ( 0.f != fSpeed)
	{
		// �̵� ����
		vec2 vDir = m_vVelocity;
		vDir.Normalize();

		vec2 vPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
		vPos += m_vVelocity * fDT;

		gameObject->GetComponent<TransformComponent>()->SetPosition(vPos);
	}
}
