#include "include.h"

CPlayerController::CPlayerController(string name) : m_Character(nullptr)
{

}

CPlayerController::~CPlayerController()
{

}

void CPlayerController::Init()
{

}

void CPlayerController::Update()
{
	
}

void CPlayerController::OnPossess(CCharacter* InCharacter)
{
	if (InCharacter->GetController() != nullptr)
	{
		InCharacter->GetController()->OnUnPossess();
	}
	InCharacter->Possessedby(this);
	SetCharacter(InCharacter);
}

void CPlayerController::OnUnPossess()
{
	CCharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter == nullptr)
	{
		return;
	}
	m_Character->UnPossesed();
	SetCharacter(nullptr);
}

void CPlayerController::SetCharacter(CCharacter* InCharacter)
{
	m_Character = InCharacter;
}
