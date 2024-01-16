#define STB_IMAGE_IMPLEMENTATION
#include "include.h"
#include <stb_image.h>

CTexture::CTexture()
{
	m_internalFormat = 0;
}

CTexture::~CTexture()
{
}

void CTexture::LoadImage(const char* path)
{
	// �̹����� �ε��ϰ� �ؽ�ó�� ����ϱ�
	if (m_texId != 0) { stbi_image_free(image); return;	}
	int width, height, channels;
	image = stbi_load(path, &width, &height, &channels, 4);
	std::cout << width << " " << height << '\n';

	if (image)
	{
		// 2. �ؽ�ó ����
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);

		// 3. �ؽ�ó ������ ����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// glGenerateMipmap(GL_TEXTURE_2D);

		// 4. �ؽ�ó ���ε�
		// glBindTexture(GL_TEXTURE_2D, 0);

		// Set the texture uniform in the shader
		// glUseProgram(programID);			// ���α׷� Ȱ��ȭ
		// GLuint texLoc = glGetUniformLocation(programID, "u_Image");
		// 
		// glUniform1i(texLoc, 0);		// 0 corresponds to GL_TEXTURE0
		// glUseProgram(0);				// ���α׷� ��Ȱ��ȭ
	}
	else
	{
		std::cerr << "Failed to load image." << std::endl;
	}

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
