#pragma once

class CMegaman : public CCharacter
{
public:
	CMegaman(string name);
	virtual ~CMegaman();
	virtual void Init();
	virtual void Update();
	// virtual void FinalUpdate() override;
	// virtual void Render() override;
	// virtual void Destroy() override;

	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
public:
	virtual void Jump() override;
	virtual void Move();

public:
	void InitAnimation();	
	FSM* GetFSM() const { return m_FSM; }
	void SetFSM(FSM* PlayerFSM) { m_FSM = PlayerFSM; }
public:
	void TakeDamage(float damage, int dir);
	// FSM 관련 메서드
public:
	FSM* m_FSM;
	CAnimator* m_Animator;
	CRigidbody* m_Rigidbody;
	CGravity* m_Gravity;
	CCollider* m_Collider;

	vec2 m_curpos;
	int m_iDir;
	float m_speed;
	float m_MoveOffset;
	float m_Movement;
	bool m_bInvincible;
	float m_bInvincibleTimer;
	int m_StepedBlockCount;
};

