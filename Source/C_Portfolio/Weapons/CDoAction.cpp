#include "Weapons/CDoAction.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCDoAction::UCDoAction()
{
}

void UCDoAction::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner,
	const FDoActionAndHitDatas& InDoActionAndHitDatas
	)
{
	Owner = InOwner;
	World = Owner->GetWorld();

	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	Move = CHelpers::GetComponent<UCMoveComponent>(Owner);
	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	Status = CHelpers::GetComponent<UCStatusComponent>(Owner);

	//DoActionDatas -----------------------------------------------------------------
	DoActionDatas_1 = InDoActionAndHitDatas.DoActionDatas_1;
	DoActionDatas_2 = InDoActionAndHitDatas.DoActionDatas_2;
	DoActionDatas_3 = InDoActionAndHitDatas.DoActionDatas_3;

	Buff_DoActionDatas_1 = InDoActionAndHitDatas.Buff_DoActionDatas_1;
	Buff_DoActionDatas_2 = InDoActionAndHitDatas.Buff_DoActionDatas_2;
	Buff_DoActionDatas_3 = InDoActionAndHitDatas.Buff_DoActionDatas_3;
	//-----------------------------------------------------------------------------------

	//Spartan HitDatas-----------------------------------------------------------------
	Spartan_HitDatas_1 = InDoActionAndHitDatas.Spartan_HitDatas_1;
	Spartan_HitDatas_2 = InDoActionAndHitDatas.Spartan_HitDatas_2;
	Spartan_HitDatas_3 = InDoActionAndHitDatas.Spartan_HitDatas_3;

	Spartan_Buff_HitDatas_1 = InDoActionAndHitDatas.Spartan_Buff_HitDatas_1;
	Spartan_Buff_HitDatas_2 = InDoActionAndHitDatas.Spartan_Buff_HitDatas_2;
	Spartan_Buff_HitDatas_3 = InDoActionAndHitDatas.Spartan_Buff_HitDatas_3;
	//------------------------------------------------------------------------------------

	//Boss HitDatas-----------------------------------------------------------------
	Boss_HitDatas_1 = InDoActionAndHitDatas.Boss_HitDatas_1;
	Boss_HitDatas_2 = InDoActionAndHitDatas.Boss_HitDatas_2;
	Boss_HitDatas_3 = InDoActionAndHitDatas.Boss_HitDatas_3;

	Boss_Buff_HitDatas_1 = InDoActionAndHitDatas.Boss_Buff_HitDatas_1;
	Boss_Buff_HitDatas_2 = InDoActionAndHitDatas.Boss_Buff_HitDatas_2;
	Boss_Buff_HitDatas_3 = InDoActionAndHitDatas.Boss_Buff_HitDatas_3;
	//------------------------------------------------------------------------------------

	//MBoss HitDatas-----------------------------------------------------------------
	MBoss_HitDatas_1 = InDoActionAndHitDatas.MBoss_HitDatas_1;
	MBoss_HitDatas_2 = InDoActionAndHitDatas.MBoss_HitDatas_2;
	MBoss_HitDatas_3 = InDoActionAndHitDatas.MBoss_HitDatas_3;

	MBoss_Buff_HitDatas_1 = InDoActionAndHitDatas.MBoss_Buff_HitDatas_1;
	MBoss_Buff_HitDatas_2 = InDoActionAndHitDatas.MBoss_Buff_HitDatas_2;
	MBoss_Buff_HitDatas_3 = InDoActionAndHitDatas.MBoss_Buff_HitDatas_3;
	//------------------------------------------------------------------------------------

	//Player HitDatas-----------------------------------------------------------------
	Player_HitDatas_1 = InDoActionAndHitDatas.Player_HitDatas_1;
	Player_HitDatas_2 = InDoActionAndHitDatas.Player_HitDatas_2;
	Player_HitDatas_3 = InDoActionAndHitDatas.Player_HitDatas_3;

	Player_Buff_HitDatas_1 = InDoActionAndHitDatas.Player_Buff_HitDatas_1;
	Player_Buff_HitDatas_2 = InDoActionAndHitDatas.Player_Buff_HitDatas_2;
	Player_Buff_HitDatas_3 = InDoActionAndHitDatas.Player_Buff_HitDatas_3;
	//------------------------------------------------------------------------------------

}

void UCDoAction::Tick(float InDeltaTime)
{
}

void UCDoAction::DoAction(int32 InDatasIndex)
{
	bDoingAction = true;

	ACPlayer* player = Cast<ACPlayer>(Owner);
	if (!!player)
		player->TargetAction();

	DatasIndex = InDatasIndex;
}

void UCDoAction::Begin_DoAction()
{
	bBeginAction = true;
}

void UCDoAction::End_DoAction()
{
	bDoingAction = false;
	bBeginAction = false;

	//어떤 동작이든 End_DoAction이 콜된거는 동작이 완료되었다는거임.
	//그래서 Idle 모드로
	State->SetIdleMode();

	//못움직이는 공격이었으면 움직이도록
	Move->Move();
}
