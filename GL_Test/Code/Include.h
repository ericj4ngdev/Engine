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
	PROJ_PLAYER,
	PROJ_ENEMY,
	WEAPON,
	SPAWNER,
	END = 32,
};


enum class ENEMY {
	RABBIT,
	BAT,
	GORILLA,

};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

static int PC_Idx = 0;

#define LOG(fmt, ...) \
printf("%s " fmt "\n", __FUNCTION__, ##__VA_ARGS__);

// #pragma comment(lib,"glut32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <windows.h>
using namespace std;
#include<assert.h>
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

#include "EngineFramework/Util/Func.h"
#include "EngineFramework/Util/MoreMath.h"
#include "EngineFramework/Util/Vector.h"
#include "EngineFramework/Util/Color4f.h"

#include "EngineFramework/EngineCore.h"
#include "EngineFramework/Manager/GLMgr.h"
#include "EngineFramework/Manager/CResMgr.h"

#include "EngineFramework/Manager/CTimeMgr.h"
#include "EngineFramework/Manager/CPathMgr.h"
#include "EngineFramework/Manager/CCollisionMgr.h"
#include "EngineFramework/Manager/CCamera.h"
#include "EngineFramework/Manager/CEventMgr.h"
#include "EngineFramework/Manager/CKeyMgr.h"
#include "EngineFramework/Manager/CSceneMgr.h"

#include "EngineFramework/Resource/CResource.h"
#include "EngineFramework/Resource/CTexture.h"
#include "EngineFramework/Resource/CAnimation.h"

#include "EngineFramework/Scene/CScene.h"

#include "EngineFramework/Component/CComponent.h"
#include "EngineFramework/Component/CRenderComponent.h"
#include "EngineFramework/Component/TransformComponent.h"
#include "EngineFramework/Component/ControllerComponent.h"
#include "EngineFramework/Component/CCollider.h"
#include "EngineFramework/Component/CAnimator.h"
#include "EngineFramework/Component/Zombie.h"
#include "EngineFramework/Component/CRigidbody.h"
#include "EngineFramework/Component/CGravity.h"
#include "EngineFramework/Component/Bullet.h"

#include "EngineFramework/GameFramework/CGameObject.h"
#include "EngineFramework/GameFramework/CPlayerController.h"
#include "EngineFramework/GameFramework/CCharacter.h"

// Megaman
#include "Megaman/Scene/SampleScene.h"
#include "Megaman/Scene/SStage01.h"

#include "Megaman/Object/Player/CPlayer.h"
#include "Megaman/Object/Player/CMegaman.h"
#include "Megaman/Object/Map/CBlock.h"
#include "Megaman/Object/Map/CMap.h"
#include "Megaman/Object/Enemy/CEnemy.h"
#include "Megaman/Object/Enemy/CRabbit.h"
#include "Megaman/Object/Enemy/CBat.h"
#include "Megaman/Object/Projectile/CBullet.h"
#include "Megaman/Object/Projectile/CEnemyProjectile.h"
#include "Megaman/Object/Spawner/CEnemySpawner.h"


#include "Megaman/Object/Player/State/FSM.h"
#include "Megaman/Object/Player/State/CStateBase.h"
#include "Megaman/Object/Player/State/CStateIdle.h"
#include "Megaman/Object/Player/State/CStateJump.h"
#include "Megaman/Object/Player/State/CStateRun.h"

#endif

