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
using namespace std;

#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
#include <vector>
using std::vector;
#include <list>
#include <map>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Core/EngineCore.h"
#include "Core/GLMgr.h"
#include "Manager/CResMgr.h"

#include "Manager/CPathMgr.h"
#include "CObject.h"
#include "CResource.h"

#include "CoreBase.h"
#include "MemoryMgr.h"
#include "Manager/CTimeMgr.h"
#include "CGameObject.h"

#include "Manager/CKeyMgr.h"
#include "CScene.h"
#include "Manager/CSceneMgr.h"
#include "Asset/SampleScene.h"

#include "Component/CComponent.h"
#include "Util/ITransform.h"
#include "Component/CRenderComponent.h"
#include "Component/TransformComponent.h"
#include "Component/ControllerComponent.h"
#include "Resource/CTexture.h"
#include "Util/ShaderUtil.h"

#endif




