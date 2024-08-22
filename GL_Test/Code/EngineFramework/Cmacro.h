#pragma once

#define SINGLE(type) \
public:\
static type* GetInstance()\
{\
	static type mgr;\
	return &mgr;	\
}\
private:\
	type();\
	~type();

#define COMPONENT_DEFINE_CONSTRUCTOR(CLASSNAME) \
explicit CLASSNAME(CGameObject* l_gameObject);

#define COMPONENT_CONSTRUCTOR(CLASSNAME)    \
CLASSNAME::CLASSNAME(CGameObject* l_gameObject) : CComponent(#CLASSNAME, l_gameObject)

#define fDT CTimeMgr::GetInstance()->GetfDT()
#define GetKeyDown(_KEY_) \
CKeyMgr::GetInstance()->GetKeyState(KEY::_KEY_) == KEY_STATE::DOWN

#define GetKeyHold(_KEY_) \
CKeyMgr::GetInstance()->GetKeyState(KEY::_KEY_) == KEY_STATE::HOLD

#define GetKeyUp(_KEY_) \
CKeyMgr::GetInstance()->GetKeyState(KEY::_KEY_) == KEY_STATE::UP

#define BLACK	{ 1,1,1,1 } 
#define WHITE	{ 0,0,0,1 } 
#define RED		{ 1,0,0,1 } 
#define GREEN	{ 0,1,0,1 } 
#define BLUE	{ 0,0,1,1 } 

#define EPSILON 0.0001