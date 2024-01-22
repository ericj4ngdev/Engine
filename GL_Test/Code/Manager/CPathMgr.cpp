#include "include.h"

CPathMgr::CPathMgr() : 
	m_szContentPath{}
	, m_cContentPath{}
{

}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);		// 현재 디렉토리
	// printf("m_szContentPath : %ls\n", m_szContentPath);

	int len = (int)wcslen(m_szContentPath);

	for (int i = len - 1; 0 <= i; --i) 
	{
		if ('\\' == m_szContentPath[i]) 
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
	// printf("m_szContentPath : %ls\n", m_szContentPath);
	
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, m_cContentPath, m_szContentPath, _TRUNCATE);
	printf("m_cContentPath : %s\n", m_cContentPath);
}
