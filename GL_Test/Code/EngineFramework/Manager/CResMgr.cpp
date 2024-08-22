#include "include.h"

CResMgr::CResMgr() {

}
CResMgr::~CResMgr() {
	SafeDeleteMap(m_mapTex);
	// 텍스쳐의 소멸자가 private라서 문제
	/*map<string, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); iter++) {
		delete iter->second;
	}*/
}

CTexture* CResMgr::Load(const string& _strKey, const string& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) { return pTex; }

	//string strPath = CPathMgr::GetInstance()->GetContentPath();
	// strPath += _strRelativePath;

	pTex = new CTexture;
	pTex->LoadTexture(_strRelativePath.c_str());
	pTex->GetTexture();

	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const string& _strKey)
{
	map<string, CResource*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end()) { return nullptr; }

	return (CTexture*)iter->second;
}
