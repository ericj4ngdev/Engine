#include "include.h"

CScene::CScene() 
{

}
CScene::~CScene() 
{
	// �Ҹ��� �θ𿡼� �����ؾ� �ڽĿ��� ������ ������ �ʿ����.
	// �����Ҵ��� GameObject���� �������ش�.
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++) 
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			delete m_arrObj[i][j];		// i�׷� j ��ü
		}
	}
	
	// vector�Ҹ��� �˾Ƽ�
}

void CScene::Update()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->Update();	// i�׷� j ��ü
		}
	}
}

void CScene::FinalUpdate()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->FinalUpdate();	// i�׷� j ��ü
		}
	}
}

void CScene::Render()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->Render();	// i�׷� j ��ü
		}
	}
}


