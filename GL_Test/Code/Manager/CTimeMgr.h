#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			// 프레임 사이 시간값
	double			m_dAcc;			// 누적시간 = 현재 시간
	unsigned int	m_uiCallCount;	// 함수 호출 횟수 체크
	unsigned int	m_uiFPS;		// 초당 호출 횟수

public:
	void Init();
	void Update();
	void Render();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};