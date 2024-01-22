#ifndef TEXTURE_H_
#define TEXTURE_H_

class CTexture : public CResource
{
public:
    unsigned char* image;
    GLuint m_texId;

private:
    CTexture();
    virtual ~CTexture();
    friend class CResMgr;
public:
    CTexture(const CTexture& other);
    void LoadTexture(const char* path);
    void Release();
    GLuint* GetTexture();
};

#endif