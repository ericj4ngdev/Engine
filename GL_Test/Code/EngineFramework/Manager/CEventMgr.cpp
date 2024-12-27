#include "include.h"

CEventMgr::CEventMgr(){}
CEventMgr::~CEventMgr(){}
void CEventMgr::Update()
{
	// 이전 프레임에 등록해둔 Dead Object 삭제
	for (int i = 0; i < m_vDeadObj.size(); i++)
	{
		delete m_vDeadObj[i];
	}
	m_vDeadObj.clear();

	// 이벤트 처리
	for (int i = 0; i < m_vEvent.size(); i++) 
	{
		Excute(m_vEvent[i]);
	}
	m_vEvent.clear();
}

void CEventMgr::Excute(const tEvent& eve)
{
	switch (eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		auto pRawObj = reinterpret_cast<CGameObject*>(eve.lParam);
		auto pNewObj = std::unique_ptr<CGameObject>(pRawObj);
		GROUP_TYPE eType = (GROUP_TYPE)eve.wParam;

		// 씬에 추가
		CSceneMgr::GetInstance()->GetCurScene()->AddObject(move(pNewObj), eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// Object를 dead로 변경
		// 삭제 예정 오브젝트들을 모아둔다.
		CGameObject* pDeadObj = (CGameObject*)eve.lParam;
		pDeadObj->SetDead();
		m_vDeadObj.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		CSceneMgr::GetInstance()->ChangeScene((SCENE_TYPE)eve.lParam);
	}
		break;
	}
}
