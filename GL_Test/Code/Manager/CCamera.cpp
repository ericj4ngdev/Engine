#include "include.h"

CCamera::CCamera():m_vLookAt(vec2(0,0))
{

}

CCamera::~CCamera() {

}

void CCamera::Update()
{
	if (m_pTargetObj) 
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt.x = m_pTargetObj->GetPos().x;	// y좌표 동기화는 제외 
		}
	}

	/*if (GetKeyHold(W)) {
		m_vLookAt.y += 500.0f * fDT;
	}
	if (GetKeyHold(S)) {
		m_vLookAt.y -= 500.0f * fDT;
	}
	if (GetKeyHold(A)) {
		m_vLookAt.x -= 500.0f * fDT;
	}
	if (GetKeyHold(D)) {
		m_vLookAt.x += 500.0f * fDT;
	}*/
	// printf("Camera Position : (%f, %f)\n", m_vLookAt.x, m_vLookAt.y);

	CalDiff();
}

void CCamera::CalDiff()
{
	// vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

	vec2 vResolution = vec2(GLMgr::g_screenWidth, GLMgr::g_screenHeight);
	vec2 center = vResolution / 2;
	m_vDiff = m_vLookAt - center;
}

