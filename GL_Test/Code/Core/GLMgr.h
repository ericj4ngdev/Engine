#ifndef GLMGR_H_
#define GLMGR_H_
#include "CResource.h"
#include "Resource/CTexture.h"

class GLMgr
{
	SINGLE(GLMgr);
public :	
	/*GLuint VAO;
	GLuint VBO;*/
	
	static int g_screenWidth;
	static int g_screenHeight;

	//float vertices[32] =
	//{
	//	// 위치              // 컬러
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
	//};

public:
	void Init();
	void Update();
	void Render();
	void DrawSquare();
};

#endif