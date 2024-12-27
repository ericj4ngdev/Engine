#include "include.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}	
{

}
CCollisionMgr::~CCollisionMgr() 
{

}
void CCollisionMgr::Init()
{

}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE eLeft, GROUP_TYPE eRight)
{
	// 항상 행 < 열
	UINT iRow = (UINT)eLeft;		// 행(가로) = 배열 인덱스
	UINT iCol = (UINT)eRight;		// 열(세로) = 비트

	if(iRow > iCol) 
	{
		iRow = (UINT)eRight;
		iCol = (UINT)eLeft;
	}
	
	// 해당 자리가 true이면 해제
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// 해당 위치 비트 해제
	}
	else 
	{
		m_arrCheck[iRow] |= (1 << iCol);	// 여기에 비트를 넣는다. 
	}	
}

void CCollisionMgr::Reset()
{
	// 배열을 모두 0으로 초기화
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE eLeft, GROUP_TYPE eRight)
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const auto& vecLeft = pCurScene->GetGroupObject(eLeft);
	const auto& vecRight = pCurScene->GetGroupObject(eRight);
	map<ULONGLONG, bool>::iterator iter;
	for (int i = 0; i < vecLeft.size(); i++)
	{
		// 충돌체가 없는 경우
		if (NULL == vecLeft[i]->GetComponent<CCollider>()) continue;
		for (int j = 0; j < vecRight.size(); j++)
		{
			// 충돌체가 없는 경우
			// 자기자신 충돌
			if (NULL == vecRight[j]->GetComponent<CCollider>() || vecLeft[i] == vecRight[j]) continue;
			
			CCollider* pLeftCol = vecLeft[i]->GetComponent<CCollider>();
			CCollider* pRightCol = vecRight[j]->GetComponent<CCollider>();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			// 해당 키값으로 탐색을 하는데 만약 없다면 두가지 경우
			// 1. 이전 프레임에 충돌 X
			// 2. 처음 충돌
			// 따라서 탐색 시 map에 없으면 등록해야 한다. 
			iter = m_mapColInfo.find(ID.ID);
			
			// 충돌 정보 미등록시 등록(충돌한 적 없다.)
			if (m_mapColInfo.end() == iter) 
			{
				// 이전 프레임에 충돌한 적 없으므로 false라 등록
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중
				if (iter->second) 
				{
					// 이전에도 계속 충돌 중
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) 
					{
						// 삭제 예정이면 미리 Exit
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// 이전엔 충돌 X, 첫 충돌할 거임
					// 그런데 곧바로 삭제 예정인 경우
					// 둘다 삭제 예정이 아닌 경우에만 충돌이 일어나게 한다.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else 
			{
				// 현재 충돌 X
				if (iter->second)
				{
					// 이전에는 충돌 => 충돌 탈출 시점
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

/// <summary>
/// 충돌 감지
/// </summary>
/// <param name="pLeftCol"></param>
/// <param name="pRightCol"></param>
/// <returns></returns>
bool CCollisionMgr::IsCollision(CCollider* pLeftCol, CCollider* pRightCol)
{
	vec2 vLeftPos =		pLeftCol->GetPos();
	vec2 vLeftScale =	pLeftCol->GetScale();
	vec2 vRightPos = pRightCol->GetPos();
	vec2 vRightScale = pRightCol->GetScale();

	if ((abs(vLeftPos.x - vRightPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f) && (abs(vLeftPos.y - vRightPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)) {
		return true;
	}

	return false;
}
