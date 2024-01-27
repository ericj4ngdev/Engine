#pragma once

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	JUMP,
	ATTACK,
	SIT,
	HIT,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	SIT_ATTACK,
	SKILL,
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
private:
	vec2 m_curpos;
	float m_speed;
	CRigidbody* m_rigidbody;
	CCollider* m_Collider;
	CGravity* m_pGravity;
private:
	PLAYER_STATE	m_eCurState;
	PLAYER_STATE	m_ePrevState;
	int m_iDir;
	int m_iPrevDir;
public:
	void SetSpeed(float sp) { m_speed = sp; }
};
