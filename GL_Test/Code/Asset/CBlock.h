#pragma once
#include "CGameObject.h"

enum class COLLIDE_EDGE {
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
};

enum class DIR {
	STOP,			// Á¤Áö Idle
	DOWN,			// ÀÚÀ¯ ³«ÇÏ
	UP,				// ¼öÁ÷ »ó½Â
	LFET,			// ¿ÞÂÊ °È±â
	RIGHT,			// ¿À¸¥ÂÊ °È±â
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
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

