#pragma once
class CTexture;
class CResMgr
{
	SINGLE(CResMgr);
public:
	map<string, CTexture*> m_mapTex;

	CTexture* Load(const string& _strKey, const string& _strRelativePath);
	CTexture* FindTexture(const string& _strKey);
};

