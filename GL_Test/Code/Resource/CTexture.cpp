#define STB_IMAGE_IMPLEMENTATION
#include "include.h"
#include <stb_image.h>

CTexture::CTexture()
	: m_texId(0)
	, image(0)
{

}

CTexture::~CTexture()
{
	// delete image;
	// delete m_texId;
}

CTexture::CTexture(const CTexture& other)
{

}

void CTexture::LoadTexture(const char* path)
{
	// 이미지를 로드하고 텍스처로 사용하기
	// assert(m_texId);
	// if (m_texId != 0) {  return;	}
	int width, height, channel;
	glGenTextures(1, &m_texId);
	FILE* fp = NULL;
	if (fopen_s(&fp, path, "rb")) {
		printf("ERROR : No %s. \n fail to bind %d\n", path, m_texId);
		return;
	}
	image = stbi_load_from_file(fp, &width, &height, &channel, 4);
	fclose(fp);
	if (image)
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	else
	{
		std::cerr << "Failed to load image." << std::endl;
	}

	free(image);
	
}

void CTexture::Release()
{
	glDeleteTextures(1, &m_texId);
}

GLuint* CTexture::GetTexture()
{
	if (image != NULL)
		return &m_texId;
	else
		return NULL;
}