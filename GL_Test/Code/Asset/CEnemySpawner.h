#pragma once

class CEnemy;

class CEnemySpawner : public CGameObject
{
public:
	CEnemySpawner();
	CEnemySpawner(string name);
	~CEnemySpawner();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
public:
	void SetEnemy(ENEMY eEnemy) {m_eEnemy = eEnemy;}
	void SpawnEnemy();
	bool CheckPosition();
private:
	ENEMY m_eEnemy;
	CEnemy* m_Enemy;
	bool m_bSpawn;				// 소환되었는가
	bool m_bDead;
};

