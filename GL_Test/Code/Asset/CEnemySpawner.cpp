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
	// ������ ���� �׾��ų� Delete�Ǿ����� ����
	// ��ũ�� �ȿ� �ִµ� ��ȯ�� ���Ͱ� �׾����� ��ȯ
	// ��ũ�� �ȿ� �־ ��ȯ. �׸��� ��ȯ�� ����

	// �׾����� ��ȯ
	// ��ȯ�� ���� �ȵ����� ��ȯ
	bool bInPos = CheckPosition();

	//printf("CheckPosition	m_bSpawn	m_bDead\n");
	//printf("%d				%d			%d\n", bInPos, m_bSpawn, m_bDead);
	// (1,0,1)�̾�� ���ȯ

	// ȭ�� ���̸�
	if (bInPos) {
		if (m_bSpawn == false && m_bDead)
		{
			SpawnEnemy();
			m_bSpawn = true;
			m_bDead = false;
		}
	}
	// ȭ�� ���̸�
	else {

		m_bSpawn = false;
		//// ����ִ°�?		
		//if (!m_Enemy->IsDead())
		//{
		//	
		//	m_bSpawn = false;
		//}
		//else
		//{
		//	// ����
		//	m_bSpawn = true;		// ������ false. �׷��� �ٽ� ������ �� ��ȯ ����
		//}
	}

	// �׾��ų� �����Ǿ�����
	if (m_Enemy == nullptr) return;
	if (m_Enemy->IsDead()){	m_bDead = true;	}
	
	// ��ȯ �ǰ� 
	// ��ũ�� �ۿ� ���� ��������(�̰� ���� Ư¡)
	// ��ũ�� �ȿ� ������ ����
	// ��, ������ ���� �����ִٸ� �ٽ� ���ư��� ��ȯ���� �ʴ´�. 
	// ������ ���̶� ������ ó������ �޸� ��� �ɱ�?


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
