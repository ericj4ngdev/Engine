#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t		m_szContentPath[255];
	char		m_cContentPath[255];

public:
	void Init();
	const char* GetContentPath() { return m_cContentPath; }
};

