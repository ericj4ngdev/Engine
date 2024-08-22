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

public:
	void TakeDamage(float damage, int dir);
	// FSM 관련 메서드
	
};

