#include "include.h"
#include "Func.h"
void CreateObject(CGameObject* pObj, GROUP_TYPE eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)pObj;
	evn.wParam = (DWORD_PTR)eGroup;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void DeleteObject(CGameObject* pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)pObj;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)eNext;

	CEventMgr::GetInstance()->AddEvent(evn);
}
