#ifndef O_H_
#define O_H_

enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class GROUP_TYPE {
	DEFAULT,
	MAP,
	PLAYER,
	ENEMY,
	PROJECTILE,
	WEAPON,
	END = 32,
};

// #pragma comment(lib,"glut32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <windows.h>
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
// #include <GL/glew.h>
#include <GL/glut.h>

#include "Core/EngineCore.h"
#include "Core/GLMgr.h"
#include "Manager/CResMgr.h"
#include "Util/Vector.h"
#include "Util/Quaternion.h"
#include "Util/Color4f.h"

#include "CoreBase.h"
#include "Manager/CTimeMgr.h"
#include "Manager/CPathMgr.h"
#include "Manager/CCollisionMgr.h"
#include "CResource.h"

#include "CGameObject.h"
#include "Asset/CPlayer.h"
#include "Asset/CZombie.h"
#include "Asset/CBlock.h"
#include "Asset/CMap.h"

#include "Manager/CKeyMgr.h"
#include "CScene.h"
#include "Manager/CSceneMgr.h"
#include "Asset/SampleScene.h"

#include "Component/CComponent.h"
// #include "Util/ShaderUtil.h"
#include "Component/CRenderComponent.h"
#include "Component/TransformComponent.h"
#include "Component/ControllerComponent.h"
#include "Component/CCollider.h"
#include "Component/Zombie.h"
#include "Resource/CTexture.h"

#endif




