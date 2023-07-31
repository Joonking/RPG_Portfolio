#include "Weapons/Skills/CSkill_Buff.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

void UCSkill_Buff::Pressed()
{
	//이미 BuffMode라면 리턴
	CheckTrue(Status->IsBuffMode());

	//IdleMode가 아니라면 리턴
	CheckFalse(State->IsIdleMode());
	
	//UnarmedMode라면 리턴
	CheckTrue(Weapon->IsUnarmedMode());
	
	Super::Pressed();

	//MP가 100이 찬 상황이 아니라면 리턴
	CheckFalse(Status->CheckSkillMP(100));

	State->SetSkillMode();
	Status->OnBuffMode();

	ActionData.DoAction(Owner);
}

