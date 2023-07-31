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
	//���⿡ ���� BeginOverlap �ɽÿ� ��������Ʈ�� ���� ȣ��� �Լ�.
	//�ڽĿ��� �����Ұű⿡ virtual�� �ٿ���. CDoAction �θ𿡼��� ������ �𸣴� �켱 {}�� �ݰ�, cpp������ ���� �������� �ʱ�
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
	//DoAction ���Դ��� üũ
	bool bDoingAction;
	//BeginAction ���Դ��� üũ
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




