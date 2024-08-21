#pragma once
#include "CGameObject.h"

enum class COLLIDE_EDGE {
	RIGHT,		// 0
	LEFT,		// 1
	TOP,		// 2
	BOTTOM,		// 3
	NONE,		// 4
};

enum class DIR {
	STOP,			// 0 Á¤Áö Idle
	DOWN,			// 1 ÀÚÀ¯ ³«ÇÏ
	UP,				// 2 ¼öÁ÷ »ó½Â
	LFET,			// 3 ¿ÞÂÊ °È±â
	RIGHT,			// 4 ¿À¸¥ÂÊ °È±â
	LEFT_UP,		// 5
	RIGHT_UP,		// 6
	LEFT_DOWN,		// 7
	RIGHT_DOWN,		// 8
};


class CBlock : public CGameObject
{
public:
	CBlock(string name);
	virtual ~CBlock();
	virtual void Init();
	bool LineIntersection(vec2 a, vec2 b, vec2 c, vec2 d);
	float ccw(vec2 a, vec2 b);
	float ccw(vec2 p, vec2 a, vec2 b);
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
public:
	void CheckCollideEdge(CCollider* pOther);
	void CheckObjectDirection(CCollider* pOther);

private:	
	int count = 0;
public:
	void SetCount(int c) { count = c; }

};

