#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

//����Ÿ�� Enum
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword, Spear, Bow, Dagger, Hammer, Staff, Warp, Max
};

//��ųŸ�� Enum
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Skill_1, Skill_2, Skill_3, Skill_4, Max
};

//���Ⱑ ����ɶ� ȣ�� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);
//���° ��ų�� ��������� �˷��� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSkillCoolTime, ESkillType, InSkillType, float, InCoolTime);

UCLASS( ClassGroup=(Custom))
class C_PORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//DataAsset���� ������ �迭 ����
	UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UCWeaponAsset* DataAssets[(int32)EWeaponType::Max];

public:
	//���� ���� Ÿ���� ��ȯ�ϴ� �ζ��� �Լ�
	UFUNCTION(BlueprintPure)
		FORCEINLINE EWeaponType GetType() { return Type; }

public:
	//�������Ʈ���� ȣ���� ��������Ʈ��
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FWeaponTypeChanged OnWeaponTypeChanged;   //���� Ÿ���� ����ɶ� ȣ���� ��������Ʈ

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FSkillCoolTime OnSkillCoolTime;            //��ų ���� ��Ÿ�� ǥ�ø� ���� ȣ���� ��������Ʈ

public:
	//���� ���� Ÿ�� ��ȯ �Լ�
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSwordMode() { return Type == EWeaponType::Sword; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSpearMode() { return Type == EWeaponType::Spear; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBowMode() { return Type == EWeaponType::Bow; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDaggerMode() { return Type == EWeaponType::Dagger; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsHammerMode() { return Type == EWeaponType::Hammer; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStaffMode() { return Type == EWeaponType::Staff; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == EWeaponType::Warp; }

	//�޺� ���ݽ� �����ε��� ���� �Լ�
	FORCEINLINE void IncreaseDoActionIndex() { DoActionIndex++; }
	//�޺� ���ݽ� �����ε��� ��ȯ �Լ�
	FORCEINLINE int32 GetDoActionIndex() { return DoActionIndex; }
	//�޺� ���ݽ� �����ε��� Ŭ���� �Լ�
	FORCEINLINE void ClearDoActionIndex() { DoActionIndex = 0; }

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//���� ���⿡ ���� �������� ������ �Լ���
	class ACAttachment* GetAttachment();
	class UCEquipment* GetEquipment();
	class UCDoAction* GetDoAction();
	class UCSkill* GetSkill_1();
	class UCSkill* GetSkill_2();
	class UCSkill* GetSkill_3();
	class UCSkill* GetSkill_4();

private:
	void ChangeType(EWeaponType InType);
	void SetMode(EWeaponType InType);

public:
	//���� Ÿ�� ���� �Լ���
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();
	UFUNCTION(BlueprintCallable)
		void SetSwordMode();
	UFUNCTION(BlueprintCallable)
		void SetSpearMode();
	UFUNCTION(BlueprintCallable)
		void SetBowMode();
	UFUNCTION(BlueprintCallable)
		void SetDaggerMode();
	UFUNCTION(BlueprintCallable)
		void SetHammerMode();
	UFUNCTION(BlueprintCallable)
		void SetStaffMode();
	UFUNCTION(BlueprintCallable)
		void SetWarpMode();

public:
	//�⺻ ���� 
	void DoAction();

	//��ų 1~4
	void Skill_1_Pressed();     //��ų1 ������ ��
	void SKill_1_Released();   //��ų1 ���� ��

	void Skill_2_Pressed();
	void SKill_2_Released();

	void Skill_3_Pressed();
	void SKill_3_Released();

	void Skill_4_Pressed();
	void SKill_4_Released();

private:
	//WeaponComponent�� ������ ����
	class ACharacter* Owner;
	//���� ���� Ÿ���� ������ ����
	EWeaponType Type = EWeaponType::Max;   //Max�� Unarmed Ÿ��

	//�޺� Ƚ�� ����
	int32 DoActionIndex = 0;

	//������� ������ ������ Datas ����
	UPROPERTY()
		class UCWeaponData* Datas[(int32)EWeaponType::Max];
};




