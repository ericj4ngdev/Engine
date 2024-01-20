#pragma once


class CResource
{
public:
	CResource();
	virtual ~CResource();
private:
	std::string m_strKey;			// ���ҽ� Ű
	std::string m_strRelativePath;	// ���ҽ� ��� ���
	std::string m_name;

public:
	void SetKey(const std::string& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const std::string _strPath) { m_strRelativePath = _strPath; }

	const std::string& GetKey() { return m_strKey;	}
	const std::string& GetRelativePath() {	return m_strRelativePath; }
};

 