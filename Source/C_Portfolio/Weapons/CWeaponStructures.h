#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData    //���� ���� ����ü
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //��Ÿ��
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //��Ÿ�� ���� �ӵ�
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;                      //���� �� �̵� ���� ����
	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = false;          //�þ� ���� ����
};

USTRUCT()
struct FDoActionData    //���� ���� ����ü
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //��Ÿ��
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //��Ÿ�� ���� �ӵ�
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;                      //���� �� �̵� ���� ����

public:
	void DoAction(class ACharacter* InOwner);
};

USTRUCT()
struct FHitData        //hit�� ���׼� ���� ����ü
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;               //��Ÿ��
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;                    //��Ÿ�� ���� �ӵ�
	UPROPERTY(EditAnywhere)
		float Power;                               //������ ��
	UPROPERTY(EditAnywhere)
		float Launch = 100.0f;                     //�󸶳� �и���
	UPROPERTY(EditAnywhere)
		float StopTime;                            //HitStop
	UPROPERTY(EditAnywhere)
		class USoundWave* Sound;                   //Sound
	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;              //Effect
	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;   //����Ʈ �÷��� ��ų ��ġ
	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;       //����Ʈ ũ��


public:
	void PlayMontage(class ACharacter* InOwner);

	//TakeDamage�� ȣ������ �Լ�. InAttacker : �����Ѿ�, InOther : ���� ������
	void SendDamage(class ACharacter* InAttacker, class ACharacter* InOther);

	//������ ��� ���͵��� ����� �ϴϱ� ���带 �Ű������� ����.
	void PlayHitStop(class UWorld* InWorld);
	//���� ���� �Լ�
	void PlaySound(class ACharacter* InOwner);
	//����Ʈ ���� �Լ�
	void PlayEffect(class UWorld* InWorld, const FVector& InLocation);
};

//TakeDamage�� �ι�° �Ű������� �ʿ��� FDamageEvent�� ��ӹ޾Ƽ� ����ü�� �������.
//�� ����ü�� �������ִ°���. 
//�� ����ü�� TakeDamage �̺�Ʈ�� ����� �߰����� ������ ��Ƽ� �� �� ����. 
USTRUCT()
struct FHitDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FHitData* HitData;   //TakeDamage�� ���� ������ HitData ������ �ֱ����ؼ� �߰�.
						 //TakeDamage�� �޴°����� �ش� �ڷḦ Null üũ�ϱ� ���� �����ͷ� ������.
};

UCLASS()
class C_PORTFOLIO_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
};
