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