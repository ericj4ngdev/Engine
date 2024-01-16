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
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

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
public:
	void Init();
	void Update();
public:
	KEY_STATE GetKeyState(KEY _ekey);


};


