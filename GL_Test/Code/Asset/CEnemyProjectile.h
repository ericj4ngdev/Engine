#pragma once

class CEnemyProjectile : public CGameObject
{
public:
	CEnemyProjectile();
	CEnemyProjectile(string name);
	virtual ~CEnemyProjectile();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
public :
	void Movement();
	void ScreenOut();
	void SetSpeed(float speed) { m_fSpeed = speed; };
	void SetDir(vec2 dir) { m_vDir = dir; }
private:
	float m_fSpeed;
	vec2 m_vDir;
	float m_fDamage;
};

