#include "include.h"


CEnemy::CEnemy():m_iHP(0)
				, m_fSpeed(0)
				, m_fDamage(0)
{

}

CEnemy::CEnemy(string name) : CGameObject(name)
							, m_iHP(0)
							, m_fSpeed(0)
							,m_fDamage(0)
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

vec2 CEnemy::GetPlayerPosition()
{
	// 현재 씬에 있는 플레이어
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
	// vRenderPos.x의 초기값이 0일 때 예외처리
	if (vRenderPos.x <= -1 || vRenderPos.x >= GLMgr::g_screenWidth)
	{
		DeleteObject(this);
	}
}
