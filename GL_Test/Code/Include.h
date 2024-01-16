#ifndef O_H_
#define O_H_

enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
#include <vector>
using std::vector;
#include <list>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Core/EngineCore.h"
#include "Core/GLMgr.h"
#include "CObject.h"
#include "CResource.h"

#include "CoreBase.h"
#include "MemoryMgr.h"
#include "CGameObject.h"

#include "Manager/CKeyMgr.h"
#include "CScene.h"
#include "Manager/CSceneMgr.h"
#include "Asset/SampleScene.h"

#include "Component/CComponent.h"
#include "Component/CRenderComponent.h"
#include "Component/Transform.h"
#include "Resource/CTexture.h"
#include "Util/ShaderUtil.h"

#endif




