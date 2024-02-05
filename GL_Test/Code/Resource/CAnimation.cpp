#include "include.h"

CAnimation::CAnimation() :
	m_pAnimator(NULL),
	m_iCurFrm(0),
	m_fAccTime(0),
	m_bFinish(false),
	m_color(Color4f(1,1,1,1)),
	m_direction(1),
	m_vRenderPos(vec2(0,0))
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish) return;

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fD)
	{
		++m_iCurFrm;
		if (m_iCurFrm >= m_vecFrm.size())
		{
			m_iCurFrm = 0;
			m_bFinish = true;
			m_fAccTime = 0.f;
			// return;		// 인덱스가 -1되는 거 방지
		}
		else 
		{
			m_bFinish = false;
			m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fD;
		}
	}
}

void CAnimation::Render()
{
	if (m_bFinish) return;
	
	// 여기 애니메이션 구현
	CGameObject* pObj = m_pAnimator->GetGameObject();
	vec2 vPos = pObj->GetPos();							// 오브젝트 위치
	vec2 vScale = pObj->GetScale();

	m_vRenderPos = CCamera::GetInstance()->GetRenderPos(vPos);
	
	// printf("vRenderPos : (%f, %f)\n", m_vRenderPos.x, m_vRenderPos.y);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, m_pTex->m_texId);
	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(m_vRenderPos.x, m_vRenderPos.y, 0);
	glScalef(vScale.x * m_vecFrm[m_iCurFrm].dir, vScale.y, 1);
	// vPos += m_vecFrm[m_iCurFrm].vOffset;		// offset만큼 추가 이동

	DrawSprite();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

}

void CAnimation::Create(CTexture* pTex, vec2 vLT, vec2 vSliceSize, vec2 vStep, int idir, float fDuration, int iFrameCount)
{
	m_pTex = pTex;
	tAinmFrm frm = {};
	for (int i = 0; i < iFrameCount; ++i) 
	{
		frm.vLT = vLT + vStep * i;
		frm.vSlice = vSliceSize;
		frm.vTexSize = pTex->GetTextureSize();
		frm.dir = idir;
		frm.fD = fDuration;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::DrawSprite()
{
	tAinmFrm CurFrm = m_vecFrm[m_iCurFrm];
	vec2 lt = CurFrm.vLT;
	vec2 slice = CurFrm.vSlice;
	vec2 size = CurFrm.vTexSize;

	glBegin(GL_QUADS);

	glTexCoord2d(lt.x / size.x, (lt.y - slice.y) / size.y);				glVertex3d(-0.5, 0.5, -1.0);
	glTexCoord2d(lt.x / size.x, lt.y / size.y);							glVertex3d(-0.5, -0.5, -1.0);
	glTexCoord2d((lt.x + slice.x) / size.x, lt.y / size.y);				glVertex3d(0.5, -0.5, -1.0);
	glTexCoord2d((lt.x + slice.x) / size.x, (lt.y - slice.y) / size.y);	glVertex3d(0.5, 0.5, -1.0);

	glEnd();
}
