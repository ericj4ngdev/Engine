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
	strFilePath += "texture\\CastlevaniaLevel1.png";
	CreateComponent<CRenderComponent>();
	GetComponent<CRenderComponent>()->SetTexture("Background", strFilePath.c_str());
}
