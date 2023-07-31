#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapons/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"


USTRUCT(BlueprintType)
struct FDoActionAndHitDatas
{
	GENERATED_BODY()

public:
	//DoActionDatas -------------------------------------
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas_3;

	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> Buff_DoActionDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> Buff_DoActionDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> Buff_DoActionDatas_3;
	//-------------------------------------------------------

	//Spartan HitDatas -----------------------------------
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_HitDatas_3;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_Buff_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_Buff_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Spartan_Buff_HitDatas_3;
	//------------------------------------------------------

	//Boss HitDatas -----------------------------------
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_HitDatas_3;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_Buff_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_Buff_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Boss_Buff_HitDatas_3;
	//------------------------------------------------------

	//MBoss HitDatas -----------------------------------
	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_HitDatas_3;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_Buff_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_Buff_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> MBoss_Buff_HitDatas_3;
	//------------------------------------------------------

	//Player HitDatas -----------------------------------
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_HitDatas_3;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_Buff_HitDatas_1;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_Buff_HitDatas_2;
	UPROPERTY(EditAnywhere)
		TArray<FHitData> Player_Buff_HitDatas_3;
	//------------------------------------------------------
};


UCLASS()
class C_PORTFOLIO_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
		FDoActionAndHitDatas DoActionAndHitDatas;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSkill> SkillClass_1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSkill> SkillClass_2;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSkill> SkillClass_3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSkill> SkillClass_4;


public:
	UCWeaponAsset();

	//함수 내에서 WeaponData를 생성하고 그 공간을 외부에 리턴할 때는 2차 포인터를 사용.
	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);


#if WITH_EDITOR
public:
	void PostEditChangeChainProperty(struct
		FPropertyChangedChainEvent&
		PropertyChangedEvent) override;
#endif

};
