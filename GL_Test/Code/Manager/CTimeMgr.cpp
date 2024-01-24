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
	QueryPerformanceCounter(&m_llPrevCount);	// ���� Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);		// 1�ʴ� Ƚ��
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// �� ������ ���� �ð�
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/ (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ�� ���� ī��Ʈ�� ����
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


