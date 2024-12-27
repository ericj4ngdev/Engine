#include "include.h"

CScene::CScene() : m_arrObj((UINT)GROUP_TYPE::END)
{
	
}

CScene::~CScene() 
{
	// �Ҹ��� �θ𿡼� �����ؾ� �ڽĿ��� ������ ������ �ʿ����.
	// �����Ҵ��� GameObject���� �������ش�.
	//for (int i = 0; i < (UINT)GROUP_TYPE::END; i++) 
	//{
	//	for (int j = 0; j < m_arrObj[i].size(); j++)
	//	{
	//		delete m_arrObj[i][j];		// i�׷� j ��ü
	//	}
	//}
	
	// vector�Ҹ��� �˾Ƽ�
}

void CScene::Init()
{
	// ó������ 8���� �����. 
	for (int i = 0; i < MAX_CONTROLLER; i++)
	{
		unique_ptr<CPlayerController> PC = make_unique<CPlayerController>("PC " + (char)i);
		m_arrPC.push_back(move(PC));
	}

	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Init();	// i�׷� j ��ü
			}
		}
	}

	// PlayerController �ʱ�ȭ
	for (int i = 0; i < m_arrPC.size(); i++)
	{
		if (nullptr != m_arrPC[i])
		{
			m_arrPC[i]->Init();	
		}
	}
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
		auto& group = m_arrObj[i];

		for (auto iter = group.begin(); iter != group.end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render();
				++iter;
			}
			else
			{
				iter = group.erase(iter);
			}
		}
	}
}

void CScene::AddObject(std::unique_ptr<CGameObject> pGameObject, GROUP_TYPE eType)
{
	if ((UINT)eType >= (UINT)GROUP_TYPE::END) {
		printf("Invalid GROUP_TYPE: %d\n", (UINT)eType);
		return; // ��ȿ���� ���� ���̸� �ߴ�
	}
	m_arrObj[(UINT)eType].push_back(std::move(pGameObject));
}

void CScene::DeleteGroup(GROUP_TYPE eGroup)
{
	// m_arrObj[(UINT)eGroup] // �� ���Ϳ� ���� ���빰�� ��� �������־�� �Ѵ�. 
	// SafeDeleteVec<CGameObject*>(m_arrObj[(UINT)eGroup]);
	m_arrObj[(UINT)eGroup].clear();
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

	// CPlayerController* pController = m_arrPC[PC_Idx];
	auto& pController = m_arrPC[PC_Idx];

	if (pController != nullptr)
	{
		PC_Idx++;
		return pController.get();
	}
	return nullptr;
}
