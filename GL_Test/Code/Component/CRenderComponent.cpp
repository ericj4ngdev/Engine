#include "include.h"

CRenderComponent::CRenderComponent(CGameObject* l_gameObject) : CComponent("CRenderComponent", l_gameObject)
{
	m_color = Color4f(1, 1, 1, 1);
}

CRenderComponent::~CRenderComponent()
{
	
}

void CRenderComponent::Init()
{
	
}

void CRenderComponent::Update()
{
	vec2 vObjectPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	SetCenterPos(vObjectPos.x, vObjectPos.y);

	vec2 vObjectScale = gameObject->GetComponent<TransformComponent>()->GetScale();
	SetScale(vObjectScale.x, vObjectScale.y);
}

void CRenderComponent::FinalUpdate()
{
}

void CRenderComponent::Render()
{
	vec2 vRenderPos = CCamera::GetInstance()->GetRenderPos(m_centerPos);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(vRenderPos.x, vRenderPos.y, 0);
	glScalef(m_Scale.x , m_Scale.y, 1);
	
	RenderPlaneVAO();
	
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();		
}

void CRenderComponent::Destroy()
{
}

void CRenderComponent::SetTexture(const string& _strKey, const char* _strFilePath)
{
	m_texture = CResMgr::GetInstance()->Load(_strKey, _strFilePath);
	m_Texid = m_texture->m_texId;
}

void CRenderComponent::RenderPlaneVAO()
{
	glBegin(GL_QUADS);
		glTexCoord2d(0,1);      glVertex3d(-0.5, -0.5, -1.0);
		glTexCoord2d(0,0);      glVertex3d(-0.5, 0.5, -1.0);
		glTexCoord2d(1,0);		glVertex3d(0.5, 0.5,  -1.0);
		glTexCoord2d(1,1);      glVertex3d(0.5, -0.5, -1.0);
	glEnd();
}

void CRenderComponent::SetCenterPos(float x, float y)
{
	m_centerPos.x = x;
	m_centerPos.y = y;
}

void CRenderComponent::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}
