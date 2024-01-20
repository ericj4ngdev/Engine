#ifndef TEXTURE_H_
#define TEXTURE_H_

class CTexture : public CResource
{
public:
    unsigned char* image;
    GLuint m_texId;
    int m_targetGL = GL_TEXTURE_2D;

public:
    CTexture();
    virtual ~CTexture();
    CTexture(const CTexture& other);
    void LoadTexture(const char* path);
    void Release();
    GLuint* GetTexture();
};

#endif