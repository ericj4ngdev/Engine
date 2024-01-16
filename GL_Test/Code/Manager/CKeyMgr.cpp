#include "include.h"

// GetAsyncKeyState���� �����ϴ� ���� Ű���� ������ ���� �迭 ����
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
			// �������� �����־�����
			if (m_veckey[i].bPrevPush)
			{
				// HOLD�����̴�.
				m_veckey[i].eState = KEY_STATE::HOLD;
			}
			else m_veckey[i].eState = KEY_STATE::DOWN;
			m_veckey[i].bPrevPush = true;
		}		
		// Ű�� �ȴ����ִ�.		
		else 
		{
			if (m_veckey[i].bPrevPush)
			{
				// ��� �������� Ű�� ���ȴ�.
				m_veckey[i].eState = KEY_STATE::UP;
			}
			else 
			{
				// �������� Ű�� �ȴ��� �־���.
				m_veckey[i].eState = KEY_STATE::NONE;
			}
			m_veckey[i].bPrevPush = false;
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY _ekey){	return m_veckey[(int)_ekey].eState; }


