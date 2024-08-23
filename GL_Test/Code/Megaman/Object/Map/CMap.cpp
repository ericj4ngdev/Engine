#include "include.h"


CMap::CMap(string name)
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\Wood Man Stage.png";
	CreateComponent<CRenderComponent>();
	GetComponent<CRenderComponent>()->SetTexture("Background", strFilePath.c_str());
}

CMap::~CMap()
{
}

void CMap::Init()
{
	
}
