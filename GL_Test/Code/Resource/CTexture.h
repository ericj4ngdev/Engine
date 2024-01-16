#ifndef TEXTURE_H_
#define TEXTURE_H_

class CTexture :
    public CResource
{
public:
    unsigned char* image;
    GLuint m_texId;
    int m_internalFormat;

public:
    CTexture();
    virtual ~CTexture();
    void LoadImage(const char* path);
    void Release();
    GLuint* GetTexture();
};

#endif