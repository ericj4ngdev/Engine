#include "include.h"

CCamera::CCamera() {

}

CCamera::~CCamera() {

}

void CCamera::Update()
{
	if (m_pTargetObj) 
	{
		if (!m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetComponent<TransformComponent>()->GetPosition();
		}
	}

	if (GetKeyHold(UP)) {
		m_vLookAt.y += 500.0f * fDT;
	}
	if (GetKeyHold(DOWN)) {
		m_vLookAt.y -= 500.0f * fDT;
	}
	if (GetKeyHold(LEFT)) {
		m_vLookAt.x -= 500.0f * fDT;
	}
	if (GetKeyHold(RIGHT)) {
		m_vLookAt.x += 500.0f * fDT;
	}

	CalDiff();
}

void CCamera::CalDiff()
{
	// vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

	vec2 vResolution = vec2(GLMgr::g_screenWidth, GLMgr::g_screenWidth);
	vec2 center = vResolution / 2;
	m_vDiff = m_vLookAt - center;
}
