#include "include.h"

CScene::CScene() : m_arrObj((UINT)GROUP_TYPE::END)
{
	
}

CScene::~CScene() 
{
	// 소멸은 부모에서 구현해야 자식에서 일일이 구현할 필요없다.
	// 동적할당한 GameObject들을 해제해준다.
	//for (int i = 0; i < (UINT)GROUP_TYPE::END; i++) 
	//{
	//	for (int j = 0; j < m_arrObj[i].size(); j++)
	//	{
	//		delete m_arrObj[i][j];		// i그룹 j 객체
	//	}
	//}
	
	// vector소멸은 알아서
}

void CScene::Init()
{
	// 처음부터 8개를 만든다. 
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
				m_arrObj[i][j]->Init();	// i그룹 j 객체
			}
		}
	}

	// PlayerController 초기화
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
		return; // 유효하지 않은 값이면 중단
	}
	m_arrObj[(UINT)eType].push_back(std::move(pGameObject));
}

void CScene::DeleteGroup(GROUP_TYPE eGroup)
{
	// m_arrObj[(UINT)eGroup] // 이 벡터와 벡터 내용물도 모두 삭제해주어야 한다. 
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
