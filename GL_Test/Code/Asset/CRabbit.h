#pragma once

class CRigidbody;
class CCollider;
class CGravity;
class CAnimator;

enum class RABBIT_STATE 
{
    IDLE,
    JUMP,
    FALL,
    ATTACK,
};

class CRabbit : public CEnemy
{
public:
    CRabbit();
    explicit CRabbit(string name);
    virtual ~CRabbit();
    virtual void Init();
    virtual void Update();
    virtual void OnCollisionEnter(CCollider* pOther);
public:
    void UpdateState();
    void ChangeState(RABBIT_STATE newState);
    void Attack();
    void Jump();
private:
    int m_iDir;
    CRigidbody* m_rigidbody;
    CCollider* m_Collider;
    CGravity* m_pGravity;
    int m_attackCount;
    float m_attackTimer;
    float m_attackDT;
    float m_moveTimer;
    RABBIT_STATE m_eCurState;

};

