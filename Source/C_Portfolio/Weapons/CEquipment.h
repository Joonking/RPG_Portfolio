#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CEquipment.generated.h"

//Equip시에 콜해줄 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBehavior);

UCLASS()
class C_PORTFOLIO_API UCEquipment : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }

public:
	void BeginPlay(class ACharacter* InOwner, const FEquipmentData& InData);

public:
	void Equip();
	void Begin_Equip();
	void End_Equip();
	void UnEquip();

public:
	//BeginEquip시에 콜해줄 델리게이트
	FEquipmentBehavior OnBeginEquip;
	//Unequip 시에 콜해줄 델리게이트
	FEquipmentBehavior OnUnEquip;

private:
	class ACharacter* OwnerCharacter;

private:
	//Equip 중에 캐릭터가 움직일지 말지 등을 관리하기 위해서
	class UCMoveComponent* Move;
	//캐릭터의 State를 Equip으로 바꾸기 위해서
	class UCStateComponent* State;

private:
	FEquipmentData Data;   //Equipment 구조체 데이터

private:
	bool bBeginEquip;  //장착중인지 체크
	bool bEquipped;  //장착완료인지 체크



};
