#include "include.h"

UINT CCollider::g_iNextID = 0;

COMPONENT_CONSTRUCTOR(CCollider), m_ID(g_iNextID++)
{
	m_offsetPos = vec2(0, 0);
	// m_ColCount = 0;
}

void CCollider::Init()
{
	vec2 vObjectScale = gameObject->GetComponent<TransformComponent>()->GetScale();
	m_scale = vObjectScale;
}

void CCollider::Update()
{
}

void CCollider::FinalUpdate()
{
	// 오브젝트 위치를 따라다님
	m_vCurColPos = gameObject->GetPos();							 // 물리 영향 다 받은 위치 정보
	float fTop = m_vCurColPos.y + m_scale.y / 2;
	float fBottom = m_vCurColPos.y - m_scale.y / 2;
	float fLeft = m_vCurColPos.x - m_scale.x / 2;
	float fRight = m_vCurColPos.x + m_scale.x / 2;
	
	m_struEdge.m_vLT = vec2(fLeft, fTop);
	m_struEdge.m_vRT = vec2(fRight, fTop);
	m_struEdge.m_vRB = vec2(fRight, fBottom);
	m_struEdge.m_vLB = vec2(fLeft, fBottom);

	if ((m_vCurColPos - m_vPrevColPos).Length() != 0)
	{
		m_vDirection = (m_vCurColPos - m_vPrevColPos).Normalize();       // 방향
		// printf("CCollider::FinalUpdate() m_vCurColPos %f %f \n", m_vCurColPos.x, m_vCurColPos.y);
		// printf("CCollider::FinalUpdate() m_vPrevColPos %f %f \n", m_vPrevColPos.x, m_vPrevColPos.y);
	}
	else m_vDirection = vec2(0, 0);
	
	m_pos = m_vCurColPos + m_offsetPos;
	
	//assert(0 <= m_ColCount);
	m_vPrevColPos = m_vCurColPos;									 // 갱신
}

void CCollider::Render()
{
	Color4f color = RED;
	DrawRectangle(m_scale, color);
	// -100 <= m_scale <= 100
}

void CCollider::DrawRectangle(vec2 scale, Color4f color)
{	
	vec2 vRenderPos = CCamera::GetInstance()->GetRenderPos(m_pos);
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glTranslatef(vRenderPos.x, vRenderPos.y, 0);
	glScalef(scale.x, scale.y, 1);

	glBegin(GL_LINES);

	glVertex3d(-0.5, -0.5, -1.0);
	glVertex3d(-0.5, 0.5, -1.0);

	glVertex3d(-0.5, 0.5, -1.0);
	glVertex3d(0.5, 0.5, -1.0);

	glVertex3d(0.5, 0.5, -1.0);
	glVertex3d(0.5, -0.5, -1.0);

	glVertex3d(0.5, -0.5, -1.0);
	glVertex3d(-0.5, -0.5, -1.0);

	glEnd();

	glPopMatrix();
}



void CCollider::Destroy()
{
}

void CCollider::OnCollision(CCollider* pOther)
{
	gameObject->OnCollision(pOther);
}

void CCollider::OnCollisionEnter(CCollider* pOther)
{
	++m_ColCount;
	gameObject->OnCollisionEnter(pOther);
}

void CCollider::OnCollisionExit(CCollider* pOther)
{
	--m_ColCount;
	gameObject->OnCollisionExit(pOther);
}

CCollider::CCollider(const CCollider& _origin)
	: m_offsetPos(_origin.m_offsetPos)	
	, m_scale(_origin.m_scale)
	, m_ID(g_iNextID++)
{	  
}

CCollider::~CCollider()
{
}
