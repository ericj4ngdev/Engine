#pragma once

class CAnimation;

class CAnimator : public CComponent
{
public:
    COMPONENT_DEFINE_CONSTRUCTOR(CAnimator)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    virtual ~CAnimator();
private:
    map<string, CAnimation*>     m_mapAnim;
    CAnimation* m_pCurAnim;
    bool                        m_bRepeat;
private:
    CTexture* m_texture;
    GLuint m_Texid;
public:
    void CreateAnimation(const string strName, CTexture* pTex, vec2 vLT, vec2 vSliceSize, vec2 vStep, int idir, float fDuration, int iFrameCount);
    CAnimation* FindAnimation(const string& strName);
    void Play(const string& strName, bool bRepeat);

    CTexture* GetTexture() { return m_texture; }
    void SetTexture(const string& _strKey, const char* _strFilePath);
    
};
