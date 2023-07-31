#include "Components/CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent()
{

}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::ChangeType(EStateType InType)
{
	EStateType PrevType = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(PrevType, Type);
}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetBackstepMode()
{
	ChangeType(EStateType::Backstep);
}

void UCStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UCStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetSkillMode()
{
	ChangeType(EStateType::Skill);
}

void UCStateComponent::SetParkourMode()
{
	ChangeType(EStateType::Parkour);
}

void UCStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UCStateComponent::SetStunMode()
{
	ChangeType(EStateType::Stun);
}

void UCStateComponent::SetAssassinMode()
{
	ChangeType(EStateType::Assassin);
}

void UCStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}


