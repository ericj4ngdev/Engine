#include "include.h"


CEnemySpawner::CEnemySpawner() :m_Enemy(nullptr), m_iSpawnCnt(0), m_bDead(true)
{
	Init();
}

CEnemySpawner::CEnemySpawner(string name) :m_Enemy(nullptr), m_iSpawnCnt(0), m_bDead(true)
{
	CreateComponent<CCollider>();
}

CEnemySpawner::~CEnemySpawner()
{
}

void CEnemySpawner::Init()
{	
	SetScale(vec2(10, 10));
}

void CEnemySpawner::Update()
{
	bool bInPos = CheckPosition();
	// printf("\x1B[H");
	// printf("\x1B[B");
	// printf("CheckPosition	m_iSpawnCnt	\n");
	
	if (m_Enemy != nullptr) {
		m_bDead = m_Enemy->IsDead();
	}
	// printf("%d		%d		%d\n", bInPos, m_iSpawnCnt, m_bDead);
	if (bInPos) 
	{		
		// 화면 안에서 죽은 경우		
		if (m_iSpawnCnt == 0) 
		{
			SpawnEnemy();
			m_iSpawnCnt++;
		}
		if (m_Enemy != nullptr && m_bDead){	m_iSpawnCnt = -1;}
	}
	else
	{
		// 초기에 소환안된 경우 return
		if (m_Enemy == nullptr) return;
		// 안에서 죽은 경우 cnt회복 경로
		if (m_iSpawnCnt == -1) m_iSpawnCnt = 0;
		// 화면 밖에서 죽은 경우
		if (m_bDead)	m_iSpawnCnt = 0;
	}

}

void CEnemySpawner::OnCollisionEnter(CCollider* pOther)
{
}

void CEnemySpawner::SpawnEnemy()
{
	switch (m_eEnemy)
	{
	case ENEMY::RABBIT:
		m_Enemy = new CRabbit();
		break;
	case ENEMY::BAT:
		m_Enemy = new CBat();
		break;
	case ENEMY::GORILLA:
		break;
	default:
		break;
	}
	m_Enemy->SetPos(GetPos());
	m_Enemy->SetDirection();
	CreateObject(m_Enemy, GROUP_TYPE::ENEMY);
	printf("Spawn\n");
}

bool CEnemySpawner::CheckPosition()
{
	vec2 cameraPos = CCamera::GetInstance()->GetLookAt();
	if (cameraPos.x + GLMgr::g_screenWidth / 2 > GetPos().x + GetScale().x / 2 &&
		cameraPos.x - GLMgr::g_screenWidth / 2 < GetPos().x - GetScale().x / 2)
	{
		// printf("true\n");
		return true;	
	}
	// printf("false\n");
	return false;
}
