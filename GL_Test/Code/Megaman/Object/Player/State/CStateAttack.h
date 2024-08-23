#pragma once

enum class ATTACK_STATE
{
	IDLE,
	NORMAL_ATTACK,
	RUN_ATTACK,
	JUMP_ATTACK,
};

class CStateAttack : public CStateBase
{
public:
	CStateAttack(CMegaman* Character);
	~CStateAttack() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:
	ATTACK_STATE m_eCurAttackState;
	float m_AnimationTimer;
	float m_AttackDelay;
};

