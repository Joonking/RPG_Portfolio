#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

//무기타입 Enum
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword, Spear, Bow, Dagger, Hammer, Staff, Warp, Max
};

//스킬타입 Enum
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Skill_1, Skill_2, Skill_3, Skill_4, Max
};

//무기가 변경될때 호출 해줄 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);
//몇번째 스킬을 사용한지를 알려줄 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSkillCoolTime, ESkillType, InSkillType, float, InCoolTime);

UCLASS( ClassGroup=(Custom))
class C_PORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//DataAsset들을 관리할 배열 변수
	UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UCWeaponAsset* DataAssets[(int32)EWeaponType::Max];

public:
	//현재 무기 타입을 반환하는 인라인 함수
	UFUNCTION(BlueprintPure)
		FORCEINLINE EWeaponType GetType() { return Type; }

public:
	//블루프린트에서 호출할 델리게이트들
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FWeaponTypeChanged OnWeaponTypeChanged;   //무기 타입이 변경될때 호출할 델리게이트

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FSkillCoolTime OnSkillCoolTime;            //스킬 사용시 쿨타임 표시를 위해 호출할 델리게이트

public:
	//현재 무기 타입 반환 함수
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

	//콤보 공격시 공격인덱스 증가 함수
	FORCEINLINE void IncreaseDoActionIndex() { DoActionIndex++; }
	//콤보 공격시 공격인덱스 반환 함수
	FORCEINLINE int32 GetDoActionIndex() { return DoActionIndex; }
	//콤보 공격시 공격인덱스 클리어 함수
	FORCEINLINE void ClearDoActionIndex() { DoActionIndex = 0; }

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//현재 무기에 대한 정보들을 가져올 함수들
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
	//무기 타입 변경 함수들
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
	//기본 공격 
	void DoAction();

	//스킬 1~4
	void Skill_1_Pressed();     //스킬1 눌렀을 때
	void SKill_1_Released();   //스킬1 뗐을 때

	void Skill_2_Pressed();
	void SKill_2_Released();

	void Skill_3_Pressed();
	void SKill_3_Released();

	void Skill_4_Pressed();
	void SKill_4_Released();

private:
	//WeaponComponent의 소유자 변수
	class ACharacter* Owner;
	//현재 무기 타입을 저장할 변수
	EWeaponType Type = EWeaponType::Max;   //Max가 Unarmed 타입

	//콤보 횟수 변수
	int32 DoActionIndex = 0;

	//무기들의 정보를 저장할 Datas 변수
	UPROPERTY()
		class UCWeaponData* Datas[(int32)EWeaponType::Max];
};




