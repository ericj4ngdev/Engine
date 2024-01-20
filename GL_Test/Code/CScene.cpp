#include "include.h"

CScene::CScene() 
{

}
CScene::~CScene() 
{
	// �Ҹ��� �θ𿡼� �����ؾ� �ڽĿ��� ������ ������ �ʿ����.
	// �����Ҵ��� GameObject���� �������ش�.
	for (auto item : m_arrObj) {
		delete item;
	}
	// vector�Ҹ��� �˾Ƽ�
}

void CScene::Tick()
{
	for (auto item : m_arrObj) {
		item->Tick();
	}
}
