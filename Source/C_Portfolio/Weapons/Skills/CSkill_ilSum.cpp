#include "Weapons/Skills/CSkill_ilSum.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Characters/CPlayer.h"


void UCSkill_ilSum::Pressed()
{
	//IdleMode�� �ƴ϶�� ����
	CheckFalse(State->IsIdleMode());
	
	//UnarmedMode��� ����
	CheckTrue(Weapon->IsUnarmedMode());

	Super::Pressed();

	if(!Status->IsBuffMode()) //���� ��尡 �ƴ϶�� 
	{
		//���� MP üũ
		CheckFalse(Status->CheckSkillMP(10)); 
		Status->UpdateMP(-10);
	}

	State->SetSkillMode();
	
	ACPlayer* player = Cast<ACPlayer>(Owner);
	if (!!player)
		player->TargetAction();

	switch (Weapon->GetType())
	{
	case EWeaponType::Sword:
		break;
	case EWeaponType::Spear:
		ActionData_Spear.DoAction(Owner);


		break;
	case EWeaponType::Bow:
		break;
	case EWeaponType::Dagger:
		break;
	case EWeaponType::Hammer:
		break;
	case EWeaponType::Staff:
		break;
	case EWeaponType::Warp:
		break;
	case EWeaponType::Max:
		break;
	default:
		break;
	}

}


