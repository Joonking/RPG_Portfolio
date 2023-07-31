#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CWeaponAsset.h"
#include "CDoAction.generated.h"


UCLASS(Abstract)
class C_PORTFOLIO_API UCDoAction : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }

public:
	UCDoAction();

	virtual void BeginPlay(class ACAttachment* InAttachment, class UCEquipment* InEquipment,
		class ACharacter* InOwner, const FDoActionAndHitDatas& InDoActionAndHitDatas
		);
	virtual void Tick(float InDeltaTime);

public:
	virtual void DoAction(int32 InDatasIndex);
	virtual void Begin_DoAction();
	virtual void End_DoAction();

public:
	//무기에 적이 BeginOverlap 될시에 델리게이트를 통해 호출될 함수.
	//자식에서 정의할거기에 virtual을 붙여줌. CDoAction 부모에서는 뭐할지 모르니 우선 {}로 닫고, cpp에서는 따로 정의하지 않기
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, UShapeComponent* InCollision, class ACharacter* InOther) { }

	UFUNCTION()
		virtual void OnAttachmentCollision() { }

	UFUNCTION()
		virtual void OffAttachmentCollision() { }

protected:
	class ACharacter* Owner;
	class UWorld* World;

	//State, Move, Weapon Component
	class UCStateComponent* State;
	class UCMoveComponent* Move;
	class UCWeaponComponent* Weapon;
	class UCStatusComponent* Status;

protected:
	//DoAction 들어왔는지 체크
	bool bDoingAction;
	//BeginAction 들어왔는지 체크
	bool bBeginAction;  

	//DoActionDatas -------------------------------------
	TArray<FDoActionData> DoActionDatas_1;
	TArray<FDoActionData> DoActionDatas_2;
	TArray<FDoActionData> DoActionDatas_3;

	TArray<FDoActionData> Buff_DoActionDatas_1;
	TArray<FDoActionData> Buff_DoActionDatas_2;
	TArray<FDoActionData> Buff_DoActionDatas_3;
	//-------------------------------------------------------

	//Spartan HitDatas -----------------------------------
	TArray<FHitData> Spartan_HitDatas_1;
	TArray<FHitData> Spartan_HitDatas_2;
	TArray<FHitData> Spartan_HitDatas_3;

	TArray<FHitData> Spartan_Buff_HitDatas_1;
	TArray<FHitData> Spartan_Buff_HitDatas_2;
	TArray<FHitData> Spartan_Buff_HitDatas_3;
	//------------------------------------------------------

	//Boss HitDatas -----------------------------------
	TArray<FHitData> Boss_HitDatas_1;
	TArray<FHitData> Boss_HitDatas_2;
	TArray<FHitData> Boss_HitDatas_3;

	TArray<FHitData> Boss_Buff_HitDatas_1;
	TArray<FHitData> Boss_Buff_HitDatas_2;
	TArray<FHitData> Boss_Buff_HitDatas_3;
	//------------------------------------------------------

	//MBoss HitDatas -----------------------------------
	TArray<FHitData> MBoss_HitDatas_1;
	TArray<FHitData> MBoss_HitDatas_2;
	TArray<FHitData> MBoss_HitDatas_3;

	TArray<FHitData> MBoss_Buff_HitDatas_1;
	TArray<FHitData> MBoss_Buff_HitDatas_2;
	TArray<FHitData> MBoss_Buff_HitDatas_3;
	//------------------------------------------------------

	//Player HitDatas -----------------------------------
	TArray<FHitData> Player_HitDatas_1;
	TArray<FHitData> Player_HitDatas_2;
	TArray<FHitData> Player_HitDatas_3;

	TArray<FHitData> Player_Buff_HitDatas_1;
	TArray<FHitData> Player_Buff_HitDatas_2;
	TArray<FHitData> Player_Buff_HitDatas_3;
	//------------------------------------------------------

	int32 DatasIndex=0;
};




