#include "include.h"

// GetAsyncKeyState에서 제공하는 가상 키값과 순서가 같은 배열 생성
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	// LEFT,
	VK_RIGHT,	// RIGHT,
	VK_UP,		// UP,
	VK_DOWN,	// DOWN,
	'Q',		// Q,
	'W',		// W,
	'E',		// E,
	'R',		// R,
	'A',		// A,
	'S',		// S,
	'D',		// D,
	'F',		// F,
	VK_MENU,	// ALT,
	VK_CONTROL,	// CTRL,
	VK_LSHIFT,	// LSHIFT,
	VK_SPACE,	// SPACE,
	VK_RETURN,	// ENTER,
	VK_ESCAPE,	// ESC,
	// 
	// LAST
};

CKeyMgr::CKeyMgr() {

}
CKeyMgr::~CKeyMgr() {

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		m_veckey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) 
		{
			// 이전에도 눌려있었으면
			if (m_veckey[i].bPrevPush)
			{
				// HOLD상태이다.
				m_veckey[i].eState = KEY_STATE::HOLD;
			}
			else m_veckey[i].eState = KEY_STATE::DOWN;
			m_veckey[i].bPrevPush = true;
		}		
		// 키가 안눌려있다.		
		else 
		{
			if (m_veckey[i].bPrevPush)
			{
				// 대신 직전까지 키가 눌렸다.
				m_veckey[i].eState = KEY_STATE::UP;
			}
			else 
			{
				// 예전부터 키가 안눌려 있었다.
				m_veckey[i].eState = KEY_STATE::NONE;
			}
			m_veckey[i].bPrevPush = false;
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY _ekey){	return m_veckey[(int)_ekey].eState; }


