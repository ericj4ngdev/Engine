#pragma once

class CAnimator;
class CTexture;

struct tAinmFrm
{
	vec2 vLT;			// �»�� ��ġ
	vec2 vSlice;		// ������ ����
	vec2 vOffset;		// ������
	vec2 vTexSize;		// �̹��� ��ü ũ��
	int dir;			// ����
	float fD;			// ������ �ð� ����
};

class CAnimation
{
private:
	string				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAinmFrm>	m_vecFrm;			// ��� ������ ����
	Color4f				m_color;
	vec2				texSize;
	vec2				m_vRenderPos;
	int					m_direction;
	int					m_iCurFrm;			// ������� �ִϸ��̼��� ���� ������
	float				m_fAccTime;			// �ð� ����
	bool				m_bFinish;
public:
	void Update();
	void Render();
public:
	const string& GetName() { return m_strName; }
	void Create(CTexture* pTex, vec2 vLT, vec2 vSliceSize, vec2 vStep, int idir, float fDuration, int iFrameCount);
	bool IsFinished() { return m_bFinish; }
	void SetFinished(bool b) { m_bFinish = b; }
	void SetFrame(int iFrameIdx) 
	{
		m_bFinish = false;
		m_iCurFrm = iFrameIdx;
		m_fAccTime = 0.f;
	}
	void SetDirection(int dir) { m_direction = dir; }
	tAinmFrm& GetFrame(int idx) { return m_vecFrm[idx]; }
	int GetCurFrame() { return m_iCurFrm; }
	size_t GetMaxFrame() { return m_vecFrm.size(); }
	vec2 GetRenderPos() {return m_vRenderPos; }
	void DrawSprite();
	void SetColor(Color4f c) { m_color = c; };
private:
	void SetName(const string& name) { m_strName = name; }
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

