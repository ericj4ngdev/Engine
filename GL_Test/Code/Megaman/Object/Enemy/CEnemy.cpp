#include "include.h"


CEnemy::CEnemy():m_iHP(0)
				, m_fSpeed(0)
				, m_fDamage(0)
	, m_eCurState(ENEMY_STATE::IDLE)
{

}

CEnemy::CEnemy(string name) : CGameObject(name)
							, m_iHP(0)
							, m_fSpeed(0)
							,m_fDamage(0)
							, m_eCurState(ENEMY_STATE::IDLE)
{
	
}

CEnemy::~CEnemy() = default;

void CEnemy::Init()
{
}

void CEnemy::Update()
{
	
}

void CEnemy::OnCollisionEnter(CCollider* pOther)
{
	
}

void CEnemy::OnCollision(CCollider* pOther)
{

}

vec2 CEnemy::GetPlayerPosition()
{
	// ���� ���� �ִ� �÷��̾�
	vector<CGameObject*> player_group = CSceneMgr::GetInstance()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER);
	if (player_group.empty())
	{
		printf("not find player");
		return vec2(0,0);
	}
	CPlayer* m_cPlayer = (CPlayer*)player_group[0];			// ?
	return m_cPlayer->GetPos();
}

void CEnemy::ScreenOut()
{
	vec2 vRenderPos = GetComponent<CAnimator>()->GetAnimation()->GetRenderPos();	
	// vRenderPos.x�� �ʱⰪ�� 0�� �� ����ó��
	if (vRenderPos.x < -1 || vRenderPos.x > GLMgr::g_screenWidth)
	{
		DeleteObject(this);
	}
}

void CEnemy::SetDirection()
{
	vec2 playerPos = GetPlayerPosition();
	// vec2 dir = (playerPos - GetPos()).Normalize();

	if (playerPos.x < GetPos().x) m_iDir = -1;
	else m_iDir = 1;

	// m_iDir = dir.x > 0 ? 1 : -1;			// ������ �ݴ�
}

void CEnemy::ChangeState(ENEMY_STATE newState)
{
	if (m_eCurState == newState) return;
	m_eCurState = newState;
}
