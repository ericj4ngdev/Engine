#ifndef GLMGR_H_
#define GLMGR_H_
#include "EngineFramework/Resource/CResource.h"
#include "EngineFramework/Resource/CTexture.h"

class GLMgr
{
	SINGLE(GLMgr);
public :	
	static int g_screenWidth;
	static int g_screenHeight;

public:
	void Init();
	void Update();
	void Render();
	void Resize(int width, int height);
};

#endif