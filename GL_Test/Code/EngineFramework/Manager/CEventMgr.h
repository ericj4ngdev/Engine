#pragma once


struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR 	lParam;
	DWORD_PTR 	wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vEvent;
	vector<CGameObject*> m_vDeadObj;
public:
	void Update();
private:
	void Excute(const tEvent& eve);
public:
	void AddEvent(tEvent& eve) { m_vEvent.push_back(eve); }

};

