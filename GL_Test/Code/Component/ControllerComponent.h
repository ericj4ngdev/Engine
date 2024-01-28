#pragma once

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	JUMP,
	FALL,
	ATTACK,
	SIT,
	HIT,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	IDLE,
	NORMAL,
	RUN_ATTACK,
	JUMP_ATTACK,
};


class CRigidbody;
class CCollider;
class CGravity;

class ControllerComponent : public CComponent
{
public:
	ControllerComponent(CGameObject* l_gameObject);
	~ControllerComponent();
	void Init() override;
	void Update() override;
	void FinalUpdate() override;
	void Render() override;
	void Destroy() override;
public:
	void Control();
	void SpecialAttack();
	void UpdateState();
	void UpdateAnimation();
	void SetState(PLAYER_STATE state) { m_eCurState = state; }
	void ChangeState(PLAYER_STATE newState);
	void ChangeAttackState(PLAYER_ATTACK_STATE attackState);
	void UpdateAttack();
private:
	vec2 m_curpos;
	float m_speed;
	CRigidbody* m_rigidbody;
	CCollider* m_Collider;
	CGravity* m_pGravity;
private:
	PLAYER_STATE	m_eCurState;
	PLAYER_STATE	m_ePrevState;
	PLAYER_ATTACK_STATE	m_eCurAttackState;
	int m_iDir;
	int m_iPrevDir;
	bool m_bMoveable;
	float animationTimer;
private:
	float m_attackDT;
	float m_attackTimer;
	int m_attackCount;
public:
	void SetSpeed(float sp) { m_speed = sp; }
};
