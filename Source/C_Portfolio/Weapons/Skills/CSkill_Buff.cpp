#include "Weapons/Skills/CSkill_Buff.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

void UCSkill_Buff::Pressed()
{
	//�̹� BuffMode��� ����
	CheckTrue(Status->IsBuffMode());

	//IdleMode�� �ƴ϶�� ����
	CheckFalse(State->IsIdleMode());
	
	//UnarmedMode��� ����
	CheckTrue(Weapon->IsUnarmedMode());
	
	Super::Pressed();

	//MP�� 100�� �� ��Ȳ�� �ƴ϶�� ����
	CheckFalse(Status->CheckSkillMP(100));

	State->SetSkillMode();
	Status->OnBuffMode();

	ActionData.DoAction(Owner);
}

