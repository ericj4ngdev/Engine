#pragma once

enum class KEY_STATE {
	NONE,
	DOWN,
	HOLD,
	UP,
};

enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	A,
	S,
	D,
	F,
	Z,
	X,
	C,
	V,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LRTN,
	RBTN,

	LAST
};

struct tKeyInfo 
{
	KEY_STATE	eState;		// 키 상태값
	bool		bPrevPush;		// 이전 프레임 키 상태값
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_veckey;
	vec2			 m_vCurMousePos;
public:
	void Init();
	void Update();
public:
	KEY_STATE GetKeyState(KEY _ekey) { return m_veckey[(int)_ekey].eState; }
	vec2 GetMousePos() { return m_vCurMousePos; }

};


