#include "include.h"

CBlock::CBlock(string name) : CGameObject(name)
{
	Init();
}

CBlock::~CBlock() = default;

void CBlock::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\block.png";
	CreateComponent<CRenderComponent>();
	CreateComponent<CCollider>();
	GetComponent<CRenderComponent>()->SetTexture("Block", strFilePath.c_str());
	

}
