#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			// ������ ���� �ð���
	double			m_dAcc;			// �����ð� = ���� �ð�
	unsigned int	m_uiCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	unsigned int	m_uiFPS;		// �ʴ� ȣ�� Ƚ��

public:
	void Init();
	void Update();
	void Render();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};