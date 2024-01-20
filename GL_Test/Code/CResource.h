#pragma once


class CResource
{
public:
	CResource();
	virtual ~CResource();
private:
	std::wstring m_strKey;			// 리소스 키
	std::wstring m_strRelativePath;	// 리소스 상대 경로
	std::string m_name;

public:
	void SetKey(const std::wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const std::wstring _strPath) { m_strRelativePath = _strPath; }

	const std::wstring& GetKey() { return m_strKey;	}
	const std::wstring& GetRelativePath() {	return m_strRelativePath; }
};

 