#include "include.h"


COMPONENT_CONSTRUCTOR(CCollider)
{

}

void CCollider::Init()
{
	
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
	Vector4<GLfloat> color = RED;
	DrawRectangle(1, 1, color);
}

void CCollider::DrawRectangle(float width, float height,const Vector4<GLfloat>& color)
{	
	glPushMatrix();
	// glColor4f(color.x, color.y, color.z, color.w);
	glColor4f(1, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glBegin(GL_LINES);
	glVertex2d(-width / 2.0, -height / 2.0);
	glVertex2d(-width / 2.0, height / 2.0);
			 
	glVertex2d(-width / 2.0, height / 2.0);
	glVertex2d(width / 2.0, height / 2.0);
			 
	glVertex2d(width / 2.0, height / 2.0);
	glVertex2d(width / 2.0, -height / 2.0);
			 
	glVertex2d(width / 2.0, -height / 2.0);
	glVertex2d(-width / 2.0, -height / 2.0);
	glEnd();
	glPopMatrix();
}



void CCollider::Destroy()
{
}

CCollider::CCollider()
{
}

CCollider::~CCollider()
{
}
