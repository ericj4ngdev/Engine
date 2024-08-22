#include "include.h"

CScene::CScene()
{
	// ó������ 8���� �����. 
	for (int i = 0; i < MAX_CONTROLLER; i++)
	{
		CPlayerController* PC = new CPlayerController("PC "+(char)i);
		m_arrPC.push_back(PC);
	}
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
			if (!m_arrObj[i][j]->IsDead()) 
			{
				m_arrObj[i][j]->Update();	// i�׷� j ��ü
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
			m_arrObj[i][j]->FinalUpdate();	// i�׷� j ��ü
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
				(*iter)->Render();	// i�׷� j ��ü
				++iter;
			}
			else 
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE eGroup)
{
	// m_arrObj[(UINT)eGroup] // �� ���Ϳ� ���� ���빰�� ��� �������־�� �Ѵ�. 
	SafeDeleteVec<CGameObject*>(m_arrObj[(UINT)eGroup]);
}

void CScene::DeleteAll()
{
	for(UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

CPlayerController* CScene::GetController()
{
	if (PC_Idx < 0 || PC_Idx >= MAX_CONTROLLER)
	{
		cout << "Max PC_Idx";
		return nullptr;
	}

	CPlayerController* pController = m_arrPC[PC_Idx];

	if (pController != nullptr)
	{
		PC_Idx++;
		return pController;
	}
	return nullptr;
}
