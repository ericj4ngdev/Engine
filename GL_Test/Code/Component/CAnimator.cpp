#include "include.h"

COMPONENT_CONSTRUCTOR(CAnimator) , m_bRepeat(false)
{

}

void CAnimator::Init()
{
	// if (nullptr != m_pCurAnim) m_pCurAnim->Init();
}

void CAnimator::Update()
{
	if (nullptr != m_pCurAnim) 
	{
		m_pCurAnim->Update();

		if (m_bRepeat && m_pCurAnim->IsFinished()) 
		{
			// 반복 재생
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::FinalUpdate()
{
	// if (nullptr != m_pCurAnim) m_pCurAnim->FinalUpdate();
}

void CAnimator::Render()
{
	if (nullptr != m_pCurAnim) m_pCurAnim->Render();
}

void CAnimator::Destroy()
{
}

CAnimator::~CAnimator()
{
	// 애니메이션 지우기
	SafeDeleteMap(m_mapAnim);
}

void CAnimator::CreateAnimation(const string strName, CTexture* pTex, vec2 vLT, vec2 vSliceSize, vec2 vStep, int idir, float fDuration, int iFrameCount)
{
	CAnimation* pAnim = FindAnimation(strName);
	assert(nullptr == pAnim);
	
	pAnim = new CAnimation();
	
	pAnim->SetName(strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(pTex, vLT, vSliceSize, vStep, idir, fDuration, iFrameCount);

	m_mapAnim.insert(make_pair(strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const string& strName)
{
	map<string, CAnimation*>::iterator iter = m_mapAnim.find(strName);

	if(iter== m_mapAnim.end())
		return nullptr;

	return iter->second;
}


void CAnimator::Play(const string& strName, bool bRepeat)
{
	m_pCurAnim = FindAnimation(strName);
	m_bRepeat = bRepeat;
}

void CAnimator::SetTexture(const string& _strKey, const char* _strFilePath)
{
	m_texture = CResMgr::GetInstance()->Load(_strKey, _strFilePath);
	m_Texid = m_texture->m_texId;
}