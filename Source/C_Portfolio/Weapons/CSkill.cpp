#include "Weapons/CSkill.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMoveComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"

UCSkill::UCSkill()
{
}

void UCSkill::BeginPlay(ACharacter* InOwner)
{
	Owner = InOwner;

	Move = CHelpers::GetComponent<UCMoveComponent>(Owner);
	Status = CHelpers::GetComponent<UCStatusComponent>(Owner);
	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);

}

void UCSkill::Pressed()
{
}

void UCSkill::Released()
{
}
