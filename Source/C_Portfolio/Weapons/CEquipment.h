#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CEquipment.generated.h"

//Equip�ÿ� ������ ��������Ʈ
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
	//BeginEquip�ÿ� ������ ��������Ʈ
	FEquipmentBehavior OnBeginEquip;
	//Unequip �ÿ� ������ ��������Ʈ
	FEquipmentBehavior OnUnEquip;

private:
	class ACharacter* OwnerCharacter;

private:
	//Equip �߿� ĳ���Ͱ� �������� ���� ���� �����ϱ� ���ؼ�
	class UCMoveComponent* Move;
	//ĳ������ State�� Equip���� �ٲٱ� ���ؼ�
	class UCStateComponent* State;

private:
	FEquipmentData Data;   //Equipment ����ü ������

private:
	bool bBeginEquip;  //���������� üũ
	bool bEquipped;  //�����Ϸ����� üũ



};
