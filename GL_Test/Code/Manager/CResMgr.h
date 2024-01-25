#pragma once
class CResource;
class CTexture;

class CResMgr
{
	SINGLE(CResMgr);
public:
	map<string, CResource*> m_mapTex;			// ���� CTexture*����

	CTexture* Load(const string& _strKey, const string& _strRelativePath);
	CTexture* FindTexture(const string& _strKey);
};