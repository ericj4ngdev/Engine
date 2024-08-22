#pragma once
class CCollider;

union COLLIDER_ID {
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT	m_arrCheck[(UINT)GROUP_TYPE::END];
public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE eLeft,GROUP_TYPE eRight);
	void Reset();
	void CollisionGroupUpdate(GROUP_TYPE eLeft, GROUP_TYPE eRight);
	bool IsCollision(CCollider* pLeftCol, CCollider* pRightCol);
};

