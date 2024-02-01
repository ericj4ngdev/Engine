#pragma once
class CGameObject;

class CCamera
{
	SINGLE(CCamera);
private:
	vec2			m_vLookAt;		// 카메라 보는 위치
	vec2			m_vPrevLookAt;	// 이전 프레임 위치
	CGameObject*	m_pTargetObj;	// 타겟 오브젝트 
	vec2			m_vDiff;		// 화면 중심 좌표와 카메라 LookAt차이값
public:
	void SetLookAt(vec2 vLook) { m_vLookAt = vLook; }
	void SetTarget(CGameObject* pTarget) { m_pTargetObj = pTarget; }
	vec2 GetRenderPos(vec2 vObjPos){ return vObjPos - m_vDiff; }	// 원래 좌표 - 차이값
	vec2 GetLookAt() { return m_vLookAt; }
public:
	void Update();
private:
	void CalDiff();
};

