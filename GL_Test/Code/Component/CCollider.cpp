#include "include.h"

UINT CCollider::g_iNextID = 0;

COMPONENT_CONSTRUCTOR(CCollider), m_ID(g_iNextID++)
{
	m_offsetPos = vec2(0, 0);
}

void CCollider::Init()
{
	// m_scale = vec2(100, 100);
}

void CCollider::Update()
{
}

void CCollider::FinalUpdate()
{
	// 오브젝트 위치를 따라다님
	vec2 vObjectPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	m_pos = vObjectPos + m_offsetPos;	
}

void CCollider::Render()
{
	Color4f color = RED;
	DrawRectangle(m_scale, color);
	// -100 <= m_scale <= 100
}

void CCollider::DrawRectangle(vec2 scale, Color4f color)
{	
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glTranslatef(m_pos.x, m_pos.y, 0);
	glScalef(scale.x, scale.y, 1);

	glBegin(GL_LINES);
	glVertex3d(-scale.x / 200.0, -scale.y / 200.0, -1.0);
	glVertex3d(-scale.x / 200.0, scale.y / 200.0, -1.0);

	glVertex3d(-scale.x / 200.0, scale.y / 200.0, -1.0);
	glVertex3d(scale.x / 200.0, scale.y / 200.0, -1.0);

	glVertex3d(scale.x / 200.0, scale.y / 200.0, -1.0);
	glVertex3d(scale.x / 200.0, -scale.y / 200.0, -1.0);

	glVertex3d(scale.x / 200.0, -scale.y / 200.0, -1.0);
	glVertex3d(-scale.x / 200.0, -scale.y / 200.0, -1.0);
	glEnd();

	glPopMatrix();
}



void CCollider::Destroy()
{
}

void CCollider::OnCollision(CCollider* pOther)
{
}

void CCollider::OnCollisionEnter(CCollider* pOther)
{
}

void CCollider::OnCollisionExit(CCollider* pOther)
{
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
