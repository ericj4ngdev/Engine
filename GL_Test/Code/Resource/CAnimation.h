#pragma once

class CAnimator;
class CTexture;

struct tAinmFrm
{
	vec2 vLT;     // 좌상단 위치
	vec2 vSlice;  // 사이즈 영역
	vec2 vOffset;	// 오프셋
	vec2 vTexSize;		// 이미지 전체 크기
	float fD; // 프레임 시간 간격
};

class CAnimation
{
private:
	string				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAinmFrm>	m_vecFrm;			// 모든 프레임 정보
	Color4f				m_color;
	vec2 texSize;
	int					m_iCurFrm;			// 재생중인 애니메이션의 현재 프레임
	float				m_fAccTime;			// 시간 누적
	bool				m_bFinish;
public:
	void Update();
	void Render();
public:
	const string& GetName() { return m_strName; }
	void Create(CTexture* pTex, vec2 vLT, vec2 vSliceSize, vec2 vStep, float fDuration, int iFrameCount);
	bool IsFinished() { return m_bFinish; }
	void SetFrame(int iFrameIdx) 
	{
		m_bFinish = false;
		m_iCurFrm = iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAinmFrm& GetFrame(int idx) { return m_vecFrm[idx]; }
	size_t GetMaxFrame() { return m_vecFrm.size(); }
	void DrawSprite();
private:
	void SetName(const string& name) { m_strName = name; }
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

