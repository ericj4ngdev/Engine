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
	// �̹����� �ε��ϰ� �ؽ�ó�� ����ϱ�
	// assert(m_texId);
	if (m_texId != 0) {  return;	}
	int width, height, channels;

	image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	std::cout << width << " " << height << '\n';
	std::cout << "Channels: " << channels << std::endl;

	if (image)
	{
		// 1. �ؽ�ó ����
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);

		// 2. set the texture wrapping parameters to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// 3. �ؽ�ó ������ ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load image." << std::endl;
	}

	// GetTexture();
	stbi_image_free(image);
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