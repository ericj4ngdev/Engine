#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;
	double			m_dAcc;
	unsigned int	m_uiCallCount;
	unsigned int	m_uiFPS;

public:
	void Init();
	void Update();
	void Render();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};