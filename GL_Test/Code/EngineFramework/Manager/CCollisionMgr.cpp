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
	// �׻� �� < ��
	UINT iRow = (UINT)eLeft;		// ��(����) = �迭 �ε���
	UINT iCol = (UINT)eRight;		// ��(����) = ��Ʈ

	if(iRow > iCol) 
	{
		iRow = (UINT)eRight;
		iCol = (UINT)eLeft;
	}
	
	// �ش� �ڸ��� true�̸� ����
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// �ش� ��ġ ��Ʈ ����
	}
	else 
	{
		m_arrCheck[iRow] |= (1 << iCol);	// ���⿡ ��Ʈ�� �ִ´�. 
	}	
}

void CCollisionMgr::Reset()
{
	// �迭�� ��� 0���� �ʱ�ȭ
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
		// �浹ü�� ���� ���
		if (NULL == vecLeft[i]->GetComponent<CCollider>()) continue;
		for (int j = 0; j < vecRight.size(); j++)
		{
			// �浹ü�� ���� ���
			// �ڱ��ڽ� �浹
			if (NULL == vecRight[j]->GetComponent<CCollider>() || vecLeft[i] == vecRight[j]) continue;
			
			CCollider* pLeftCol = vecLeft[i]->GetComponent<CCollider>();
			CCollider* pRightCol = vecRight[j]->GetComponent<CCollider>();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			// �ش� Ű������ Ž���� �ϴµ� ���� ���ٸ� �ΰ��� ���
			// 1. ���� �����ӿ� �浹 X
			// 2. ó�� �浹
			// ���� Ž�� �� map�� ������ ����ؾ� �Ѵ�. 
			iter = m_mapColInfo.find(ID.ID);
			
			// �浹 ���� �̵�Ͻ� ���(�浹�� �� ����.)
			if (m_mapColInfo.end() == iter) 
			{
				// ���� �����ӿ� �浹�� �� �����Ƿ� false�� ���
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ��
				if (iter->second) 
				{
					// �������� ��� �浹 ��
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) 
					{
						// ���� �����̸� �̸� Exit
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
					// ������ �浹 X, ù �浹�� ����
					// �׷��� ��ٷ� ���� ������ ���
					// �Ѵ� ���� ������ �ƴ� ��쿡�� �浹�� �Ͼ�� �Ѵ�.
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
				// ���� �浹 X
				if (iter->second)
				{
					// �������� �浹 => �浹 Ż�� ����
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

/// <summary>
/// �浹 ����
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
