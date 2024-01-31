#define STB_IMAGE_IMPLEMENTATION
#include "include.h"
#include <stb_image.h>

CTexture::CTexture()
	: m_texId(0)
	, image(0)
	, m_vTexSize(vec2(0,0))
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
	
	// 특정 색상 제거
	for (int i = 0; i < width * height; i++)
	{
		int r = image[i * 4];
		int g = image[i * 4 + 1];
		int b = image[i * 4 + 2];

		if (r == 128 && g == 0 && b == 128) // 마젠타색인 경우
		{
			image[i * 4 + 3] = 0; // 알파값을 0으로 설정하여 투명하게 만듦
		}
		if (r == 0 && g == 128 && b == 0) // 초록색인 경우
		{
			image[i * 4 + 3] = 0; // 알파값을 0으로 설정하여 투명하게 만듦
		}
	}

	m_vTexSize = vec2(width, height);
	// printf("m_vTexSize : %f, %f \n", m_vTexSize.x, m_vTexSize.y);
	fclose(fp);
	if (image)
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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