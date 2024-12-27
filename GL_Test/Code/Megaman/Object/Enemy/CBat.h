#pragma once

class CRigidbody;
class CCollider;
class CAnimator;
class CGravity;

class CBat : public CEnemy
{
public:
	CBat();
	CBat(string name);
	virtual ~CBat();
public:
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
public:
	void TakeDamage();
	void UpdateState();
public:
	CRigidbody* m_pRigidbody;
	CCollider* m_pCollider;
	CGravity* m_pGravity;
	bool m_bReady;
	bool m_bHit;
	float m_moveTimer;
	float m_fReadyDelay;
	float m_fSpeed;
public:
	void Move();
	void Ready();
	void BackToIdle();
};

