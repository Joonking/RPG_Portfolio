#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData    //장착 정보 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //몽타주
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //몽타주 실행 속도
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;                      //장착 시 이동 가능 여부
	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = false;          //시야 고정 여부
};

USTRUCT()
struct FDoActionData    //공격 정보 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //몽타주
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //몽타주 실행 속도
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;                      //공격 시 이동 가능 여부

public:
	void DoAction(class ACharacter* InOwner);
};

USTRUCT()
struct FHitData        //hit시 리액션 정보 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //몽타주
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //몽타주 실행 속도
	UPROPERTY(EditAnywhere)
		float Power;                               //데미지 량
	UPROPERTY(EditAnywhere)
		float Launch = 100.0f;                     //얼마나 밀릴지
	UPROPERTY(EditAnywhere)
		float StopTime;                            //HitStop
	UPROPERTY(EditAnywhere)
		class USoundWave* Sound;                   //Sound
	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;              //Effect
	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;   //이팩트 플레이 시킬 위치
	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;       //이펙트 크기


public:
	void PlayMontage(class ACharacter* InOwner);

	//TakeDamage를 호출해줄 함수. InAttacker : 공격한애, InOther : 공격 받을애
	void SendDamage(class ACharacter* InAttacker, class ACharacter* InOther);

	//월드의 모든 액터들을 멈춰야 하니까 월드를 매개변수로 받음.
	void PlayHitStop(class UWorld* InWorld);
	//사운드 실행 함수
	void PlaySound(class ACharacter* InOwner);
	//이팩트 실행 함수
	void PlayEffect(class UWorld* InWorld, const FVector& InLocation);
};

//TakeDamage의 두번째 매개변수로 필요한 FDamageEvent를 상속받아서 구조체를 만든다음.
//이 구조체를 전달해주는거임. 
//이 구조체에 TakeDamage 이벤트에 사용할 추가적인 정보를 담아서 줄 수 있음. 
USTRUCT()
struct FHitDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FHitData* HitData;   //TakeDamage를 받을 적에게 HitData 정보를 주기위해서 추가.
						 //TakeDamage를 받는곳에서 해당 자료를 Null 체크하기 위해 포인터로 보내줌.
};

UCLASS()
class C_PORTFOLIO_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
};
