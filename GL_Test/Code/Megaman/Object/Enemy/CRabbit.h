#pragma once

class CRigidbody;
class CCollider;
class CGravity;
class CAnimator;

class CRabbit : public CEnemy
{
public:
    CRabbit();
    explicit CRabbit(string name);
    virtual ~CRabbit();
    virtual void Init();
    virtual void Update();
    virtual void OnCollisionEnter(CCollider* pOther);
    virtual void OnCollision(CCollider* pOther);
public:
    virtual void UpdateState();
    virtual void TakeDamage();
public:
    void Attack();
    void Jump();
private:    
    CRigidbody* m_Rigidbody;
    CCollider* m_Collider;
    CGravity* m_pGravity;
    int m_attackCount;
    float m_fAttackTimer;
    float m_fAttackDT;
    float m_moveTimer;
};

