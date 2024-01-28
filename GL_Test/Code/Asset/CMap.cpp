#include "include.h"


CMap::CMap(string name)
{
	Init();
}

CMap::~CMap()
{
}

void CMap::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\Wood Man Stage.png";
	CreateComponent<CRenderComponent>();
	GetComponent<CRenderComponent>()->SetTexture("Background", strFilePath.c_str());
}
