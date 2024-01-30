#include "include.h"

CBlock::CBlock(string name) : CGameObject(name)
{
	Init();
}

CBlock::~CBlock() = default;

void CBlock::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\block.png";
	// CreateComponent<CRenderComponent>();
	CreateComponent<CCollider>();
	// GetComponent<CRenderComponent>()->SetTexture("Block", strFilePath.c_str());
}

bool CBlock::LineIntersection(vec2 a, vec2 b, vec2 c, vec2 d) 
{
	float ab = ccw(a, b, c) * ccw(a, b, d);
	float cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) 
	{
		if (b < a) swap(a, b);
		if (b < a) swap(a, b);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

float CBlock::ccw(vec2 a, vec2 b) { return a.Cross(b); }

float CBlock::ccw(vec2 p, vec2 a, vec2 b) { return ccw(a - p, b - p); }


void CBlock::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player") 
	{
		// ============ CheckCollideEdge ==============

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();
		
		// ============ CheckCollideEdge ==============
		COLLIDE_EDGE m_ColEdge = COLLIDE_EDGE::NONE;

		vec2 vOtherLT = pOther->GetEdges().m_vLT;
		vec2 vOtherRT = pOther->GetEdges().m_vRT;
		vec2 vOtherRB = pOther->GetEdges().m_vRB;
		vec2 vOtherLB = pOther->GetEdges().m_vLB;

		vec2 vBlockLT = GetComponent<CCollider>()->GetEdges().m_vLT;
		vec2 vBlockRT = GetComponent<CCollider>()->GetEdges().m_vRT;
		vec2 vBlockRB = GetComponent<CCollider>()->GetEdges().m_vRB;
		vec2 vBlockLB = GetComponent<CCollider>()->GetEdges().m_vLB;

		if (LineIntersection(vObjPos, vPos, vBlockLT, vBlockRT)) m_ColEdge = COLLIDE_EDGE::TOP;
		if (LineIntersection(vObjPos, vPos, vBlockRT, vBlockRB)) m_ColEdge = COLLIDE_EDGE::RIGHT;
		if (LineIntersection(vObjPos, vPos, vBlockRB, vBlockLB)) m_ColEdge = COLLIDE_EDGE::BOTTOM;
		if (LineIntersection(vObjPos, vPos, vBlockLB, vBlockLT)) m_ColEdge = COLLIDE_EDGE::LEFT;


		// ============ CheckObjectDirection ==============
		
		DIR m_Dir;
		vec2 vDir = pOther->GetDirection();
		if (vDir.x == 0 && vDir.y == 0) m_Dir = DIR::STOP;
		if (vDir.x > 0 && vDir.y > 0) m_Dir = DIR::RIGHT_UP;		// 6
		if (vDir.x < 0 && vDir.y > 0) m_Dir = DIR::LEFT_UP;			// 5
		if (vDir.x > 0 && vDir.y < 0) m_Dir = DIR::RIGHT_DOWN;		// 8
		if (vDir.x < 0 && vDir.y < 0) m_Dir = DIR::LEFT_DOWN;		// 7
		if (vDir.x == 0 && vDir.y < 0) m_Dir = DIR::DOWN;
		if (vDir.x == 0 && vDir.y > 0) m_Dir = DIR::UP;
		if (vDir.x < 0 && vDir.y == 0) m_Dir = DIR::LFET;
		if (vDir.x > 0 && vDir.y == 0) m_Dir = DIR::RIGHT;
		// return;

		float fVerticalLen = abs(vObjPos.y - vPos.y);
		float fHorizonLen = abs(vObjPos.x - vPos.x);
		float fPushY = (vObjScale.y / 2.f + vScale.y / 2.f) - fVerticalLen;
		float fPushX = (vObjScale.x / 2.f + vScale.x / 2.f) - fHorizonLen;

		vObjPos = pOtherObj->GetPos();				// transform 정보
		
		printf("m_ColEdge : %d\n", m_ColEdge);
		printf("m_Dir : %d\n", m_Dir);
		// Push
		switch (m_ColEdge)
		{
		case COLLIDE_EDGE::RIGHT:
		{
			vObjPos.x += (float)(fPushX);
		}
		break;
		case COLLIDE_EDGE::LEFT:
		{
			vObjPos.x -= (float)(fPushX);
		}
		break;
		case COLLIDE_EDGE::TOP:
		{
			switch (m_Dir)
			{
			case DIR::STOP:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::DOWN:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::UP:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::LFET:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::RIGHT:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::LEFT_UP:
			{
				if (pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					vObjPos.x += (float)(fPushX);		// 3				
			}
			break;
			case DIR::RIGHT_UP:
			{
				if (pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					vObjPos.x -= (float)(fPushX);		// 5
			}
			break;
			case DIR::LEFT_DOWN:
			{
				vObjPos.y += (float)(fPushY);		// 7
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::RIGHT_DOWN:
			{
				vObjPos.y += (float)(fPushY);		// 1
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			default:
				break;
			}
		}
		break;

		case COLLIDE_EDGE::BOTTOM:
		{
			switch (m_Dir)
			{
			case DIR::STOP:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::DOWN:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::UP:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::LFET:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::RIGHT:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::LEFT_UP:
			{
				vObjPos.y -= (float)(fPushY);		// 4
			}
			break;
			case DIR::RIGHT_UP:
			{
				vObjPos.y -= (float)(fPushY);		// 6
			}
			break;
			case DIR::LEFT_DOWN:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::RIGHT_DOWN:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
	else if (dynamic_cast<CEnemy*>(pOtherObj))
	{
		// col++;
		// 땅에 안착했음을 알려줌
		// if (pOtherObj->GetComponent<CGravity>()->GetGround()) return;
		pOtherObj->GetComponent<CGravity>()->SetGround(true);// 안착 시 중력 X


		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (float)(fPush);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// ============ CheckCollideEdge ==============

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// ============ CheckCollideEdge ==============
		COLLIDE_EDGE m_ColEdge = COLLIDE_EDGE::NONE;

		vec2 vOtherLT = pOther->GetEdges().m_vLT;
		vec2 vOtherRT = pOther->GetEdges().m_vRT;
		vec2 vOtherRB = pOther->GetEdges().m_vRB;
		vec2 vOtherLB = pOther->GetEdges().m_vLB;

		vec2 vBlockLT = GetComponent<CCollider>()->GetEdges().m_vLT;
		vec2 vBlockRT = GetComponent<CCollider>()->GetEdges().m_vRT;
		vec2 vBlockRB = GetComponent<CCollider>()->GetEdges().m_vRB;
		vec2 vBlockLB = GetComponent<CCollider>()->GetEdges().m_vLB;

		if (LineIntersection(vObjPos, vPos, vBlockLT, vBlockRT)) m_ColEdge = COLLIDE_EDGE::TOP;
		if (LineIntersection(vObjPos, vPos, vBlockRT, vBlockRB)) m_ColEdge = COLLIDE_EDGE::RIGHT;
		if (LineIntersection(vObjPos, vPos, vBlockRB, vBlockLB)) m_ColEdge = COLLIDE_EDGE::BOTTOM;
		if (LineIntersection(vObjPos, vPos, vBlockLB, vBlockLT)) m_ColEdge = COLLIDE_EDGE::LEFT;

		
		// ============ CheckObjectDirection ==============

		DIR m_Dir;
		vec2 vDir = pOther->GetDirection();
		if (vDir.x == 0 && vDir.y == 0) m_Dir = DIR::STOP;
		if (vDir.x > 0 && vDir.y > 0) m_Dir = DIR::RIGHT_UP;
		if (vDir.x < 0 && vDir.y > 0) m_Dir = DIR::LEFT_UP;
		if (vDir.x > 0 && vDir.y < 0) m_Dir = DIR::RIGHT_DOWN;
		if (vDir.x < 0 && vDir.y < 0) m_Dir = DIR::LEFT_DOWN;
		if (vDir.x == 0 && vDir.y < 0) m_Dir = DIR::DOWN;
		if (vDir.x == 0 && vDir.y > 0) m_Dir = DIR::UP;
		if (vDir.x < 0 && vDir.y == 0) m_Dir = DIR::LFET;
		if (vDir.x > 0 && vDir.y == 0) m_Dir = DIR::RIGHT;
		// return;

		float fVerticalLen = abs(vObjPos.y - vPos.y);
		float fHorizonLen = abs(vObjPos.x - vPos.x);
		float fPushY = (vObjScale.y / 2.f + vScale.y / 2.f) - fVerticalLen;
		float fPushX = (vObjScale.x / 2.f + vScale.x / 2.f) - fHorizonLen;

		vObjPos = pOtherObj->GetPos();				// transform 정보

		printf("m_ColEdge : %d\n", m_ColEdge);
		printf("m_Dir : %d\n", m_Dir);

		switch (m_ColEdge)
		{
		case COLLIDE_EDGE::RIGHT:
		{
			vObjPos.x += (float)(fPushX);
		}
		break;
		case COLLIDE_EDGE::LEFT:
		{
			vObjPos.x -= (float)(fPushX);
		}
		break;
		case COLLIDE_EDGE::TOP: 
		{
			switch (m_Dir)
			{
			case DIR::STOP:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::DOWN:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::UP:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::LFET:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::RIGHT:
			{
				vObjPos.y += (float)(fPushY);
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::LEFT_UP:
			{
				if (pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					vObjPos.x += (float)(fPushX);		// 3				
			}
			break;
			case DIR::RIGHT_UP:
			{
				if(pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					vObjPos.x -= (float)(fPushX);		// 5
			}
			break;
			case DIR::LEFT_DOWN:
			{
				vObjPos.y += (float)(fPushY);		// 7
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			case DIR::RIGHT_DOWN:
			{
				vObjPos.y += (float)(fPushY);		// 1
				pOtherObj->GetComponent<CGravity>()->SetGround(true);
			}
			break;
			default:
				break;
			}
		}
		break;

		case COLLIDE_EDGE::BOTTOM:
		{
			switch (m_Dir)
			{
			case DIR::STOP:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::DOWN:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::UP:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::LFET:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::RIGHT:
			{
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::LEFT_UP:
			{
				// if (pOtherObj->GetComponent<CGravity>()->GetGround())
					vObjPos.y -= (float)(fPushY);		// 4
			}
			break;
			case DIR::RIGHT_UP:
			{
				// if (pOtherObj->GetComponent<CGravity>()->GetGround())
					vObjPos.y -= (float)(fPushY);		// 6
			}
			break;
			case DIR::LEFT_DOWN:
			{
				// if (pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					// vObjPos.x += (float)(fPushX);		// 8
				vObjPos.y -= (float)(fPushY);
			}
			break;
			case DIR::RIGHT_DOWN:
			{
				// if (pOtherObj->GetComponent<CGravity>()->GetGround() == false)
					// vObjPos.x -= (float)(fPushX);		// 2
				vObjPos.y -= (float)(fPushY);
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
		// y좌표는 그대로... 
		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
	else if (dynamic_cast<CEnemy*>(pOtherObj))
	{
		static_cast<CEnemy*>(pOtherObj)->GetComponent<CGravity>()->SetGround(true);// 안착 시 중력 X

		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (float)(fPush);	

		static_cast<CEnemy*>(pOtherObj)->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// 땅에 안착했음을 알려줌
		pOtherObj->GetComponent<CGravity>()->SetGround(false);
	}
}

void CBlock::CheckCollideEdge(CCollider* pOther)
{
}

void CBlock::CheckObjectDirection(CCollider* pOther)
{
}
