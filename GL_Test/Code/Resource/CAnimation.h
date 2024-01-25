#pragma once

class CAnimator;
class CTexture;

struct tAinmFrm
{
	vec2 vLT;     // �»�� ��ġ
	vec2 vSlice;  // ������ ����
	vec2 vOffset;	// ������
	vec2 vTexSize;		// �̹��� ��ü ũ��
	float fD; // ������ �ð� ����
};

class CAnimation
{
private:
	string				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAinmFrm>	m_vecFrm;			// ��� ������ ����
	Color4f				m_color;
	vec2 texSize;
	int					m_iCurFrm;			// ������� �ִϸ��̼��� ���� ������
	float				m_fAccTime;			// �ð� ����
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

