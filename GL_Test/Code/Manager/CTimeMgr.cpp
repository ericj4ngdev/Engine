#include "include.h"


CTimeMgr::CTimeMgr() 
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT{}
	, m_dAcc{}
	, m_uiCallCount{}
	, m_uiFPS{}
{

}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);	// 현재 횟수
	QueryPerformanceFrequency(&m_llFrequency);		// 1초당 횟수
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// 한 프레임 사이 시간
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/ (double)m_llFrequency.QuadPart;

	// 이전 카운트를 현재 카운트로 갱신
	m_llPrevCount = m_llCurCount;
	
	++m_uiCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_uiFPS = m_uiCallCount;
		m_dAcc = 0.;
		m_uiCallCount = 0;
		printf("FPS : %d, dT : %lf \n", m_uiFPS, m_dDT);
	}
}

void CTimeMgr::Render()
{
	
}


