#include "include.h"


CSceneMgr::CSceneMgr() : m_arrScene{}, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr() {
	
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++) 
	{
		if (nullptr != m_arrScene[i]) 
		{
			delete m_arrScene[i];
		}
	}
}


void CSceneMgr::Init()
{
	// ¾À »ý¼º
	m_arrScene[(UINT)SCENE_TYPE::START] = new SampleScene;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName("Start");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new SStage01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName("STAGE_01");

	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new SampleScene;
	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new SampleScene;

	// ÇöÀç ¾À ¼³Á¤
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
	m_pCurScene->Init();
}

void CSceneMgr::Update()
{
	if (m_pCurScene == nullptr) return;
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void CSceneMgr::Render()
{
	if (m_pCurScene == nullptr) return;
	m_pCurScene->Render();
}

void CSceneMgr::ChangeScene(SCENE_TYPE eNextScene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)eNextScene];
	m_pCurScene->Enter();
}
