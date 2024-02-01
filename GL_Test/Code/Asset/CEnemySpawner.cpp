#include "include.h"


CEnemySpawner::CEnemySpawner() :m_Enemy(nullptr), m_bSpawn(false), m_bDead(true)
{
	Init();
}

CEnemySpawner::CEnemySpawner(string name) :m_Enemy(nullptr), m_bSpawn(false), m_bDead(true)
{
	Init();
}

CEnemySpawner::~CEnemySpawner()
{
}

void CEnemySpawner::Init()
{
	CreateComponent<CCollider>();
	SetScale(vec2(50, 50));
}

void CEnemySpawner::Update()
{
	// 스폰한 적이 죽었거나 Delete되었으면 스폰
	// 스크린 안에 있는데 소환한 몬스터가 죽었으면 소환
	// 스크린 안에 있어서 소환. 그리고 소환한 몬스터

	// 죽었으면 소환
	// 소환이 아직 안됐으면 소환
	bool bInPos = CheckPosition();

	//printf("CheckPosition	m_bSpawn	m_bDead\n");
	//printf("%d				%d			%d\n", bInPos, m_bSpawn, m_bDead);
	// (1,0,1)이어야 재소환

	// 화면 안이면
	if (bInPos) {
		if (m_bSpawn == false && m_bDead)
		{
			SpawnEnemy();
			m_bSpawn = true;
			m_bDead = false;
		}
	}
	// 화면 밖이면
	else {

		m_bSpawn = false;
		//// 살아있는가?		
		//if (!m_Enemy->IsDead())
		//{
		//	
		//	m_bSpawn = false;
		//}
		//else
		//{
		//	// 죽음
		//	m_bSpawn = true;		// 나가면 false. 그래야 다시 들어왔을 때 소환 가능
		//}
	}

	// 죽었거나 삭제되었으면
	if (m_Enemy == nullptr) return;
	if (m_Enemy->IsDead()){	m_bDead = true;	}
	
	// 소환 되고 
	// 스크린 밖에 가면 없어지고(이건 몬스터 특징)
	// 스크린 안에 들어오면 생성
	// 단, 생성된 적이 남아있다면 다시 돌아가도 소환되지 않는다. 
	// 생성된 적이란 조건을 처음부터 달면 어떻게 될까?


	/*if (!m_Enemy->IsDead() || m_Enemy == nullptr) 
	{
		m_bSpawn = false;
	}*/
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
		break;
	case ENEMY::GORILLA:
		break;
	default:
		break;
	}
	m_Enemy->SetPos(GetPos());
	CreateObject(m_Enemy, GROUP_TYPE::ENEMY);
	printf("Spawn\n");
}

bool CEnemySpawner::CheckPosition()
{
	vec2 cameraPos = CCamera::GetInstance()->GetLookAt();
	if (cameraPos.x + GLMgr::g_screenWidth / 2 > GetPos().x - GetScale().x / 2 &&
		cameraPos.x - GLMgr::g_screenWidth / 2 < GetPos().x + GetScale().x / 2)
	{
		// printf("true\n");
		return true;	
	}
	// printf("false\n");
	return false;
}
