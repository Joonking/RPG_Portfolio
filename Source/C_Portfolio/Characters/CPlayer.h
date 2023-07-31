#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class C_PORTFOLIO_API ACPlayer
	: public ACharacter
	, public IICharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Camera")
		class UCameraComponent* Camera;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USphereComponent* Around;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCStatusComponent* Status;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCWeaponComponent* Weapon;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCMoveComponent* Move;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class UCMontagesComponent* Montages;

	

public:
	UPROPERTY(EditAnywhere)
		FLinearColor HitColor = FLinearColor::Red;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;

public:
	ACPlayer();

	//�ܺο� Team ID�� �������ִ� �Լ� 
	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void Hitted();
	void Dead();

private:
	void End_Dead() override;

private:
	void SetAroundEnemy();

public:
	void TargetAction();

protected:
	UPROPERTY(BlueprintReadWrite)
		TArray<class ACharacter*> AroundEnemies;
	UPROPERTY(BlueprintReadWrite)
		class ACharacter* AroundEnemy = nullptr;

private:
	struct FDamageData
	{
		float Amount;   //��������
		class ACharacter* Attacker;    //������ ĳ����
		struct FHitDamageEvent* Event;
		//CWeaponStructures�� ���� �������� FHitDamageEvent ����ü
	} Damage;

private:
	float MoveForward;
	float MoveRight;

};
