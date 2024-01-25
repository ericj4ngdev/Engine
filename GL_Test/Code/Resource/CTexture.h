#ifndef TEXTURE_H_
#define TEXTURE_H_

class CTexture : public CResource
{
public:
    unsigned char* image;
    GLuint m_texId;
    vec2 m_vTexSize;
private:
    CTexture();
    virtual ~CTexture();

public:
    CTexture(const CTexture& other);
    void LoadTexture(const char* path);
    void Release();
    GLuint* GetTexture();
    const vec2& GetTextureSize(){ return m_vTexSize; }

    friend class CResMgr;
};

#endif