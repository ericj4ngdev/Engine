#include "include.h"

CScene::CScene() {

}
CScene::~CScene() 
{
	// 소멸은 부모에서 구현해야 자식에서 일일이 구현할 필요없다.
	// 동적할당한 GameObject들을 해제해준다.
	for (auto item : m_arrObj) {
		delete item;
	}
	// vector소멸은 알아서
}

void CScene::Update()
{
	for (auto item : m_arrObj) {
		item->Tick();
	}
}
