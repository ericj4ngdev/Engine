#pragma once
class CGameObject;

class CCamera
{
	SINGLE(CCamera);
private:
	vec2			m_vLookAt;		// ī�޶� ���� ��ġ
	vec2			m_vPrevLookAt;	// ���� ������ ��ġ
	CGameObject*	m_pTargetObj;	// Ÿ�� ������Ʈ 
	vec2			m_vDiff;		// ȭ�� �߽� ��ǥ�� ī�޶� LookAt���̰�
public:
	void SetLookAt(vec2 vLook) { m_vLookAt = vLook; }
	void SetTarget(CGameObject* pTarget) { m_pTargetObj = pTarget; }
	vec2 GetRenderPos(vec2 vObjPos){ return vObjPos - m_vDiff; }	// ���� ��ǥ - ���̰�
	vec2 GetLookAt() { return m_vLookAt; }
public:
	void Update();
private:
	void CalDiff();
};

