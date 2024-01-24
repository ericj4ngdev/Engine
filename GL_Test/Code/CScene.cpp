#include "include.h"

CScene::CScene() 
{

}
CScene::~CScene() 
{
	// 소멸은 부모에서 구현해야 자식에서 일일이 구현할 필요없다.
	// 동적할당한 GameObject들을 해제해준다.
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++) 
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			delete m_arrObj[i][j];		// i그룹 j 객체
		}
	}
	
	// vector소멸은 알아서
}

void CScene::Update()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead()) 
			{
				m_arrObj[i][j]->Update();	// i그룹 j 객체
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->FinalUpdate();	// i그룹 j 객체
		}
	}
}

void CScene::Render()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CGameObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render();	// i그룹 j 객체
				++iter;
			}
			else 
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}


