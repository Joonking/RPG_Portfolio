#pragma once

#include "CoreMinimal.h"
#include "ICharacter.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Spartan = 0, Boss, MBoss, Max
};

UCLASS()
class C_PORTFOLIO_API ACEnemy
	: public ACharacter
	, public IICharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FLinearColor HitColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
		EEnemyType EnemyType;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UCMoveComponent* Move;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCAIStateComponent* AIState;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	//���������� �������� C������ Team�� ������� �� ����.
	//TeamID�� ������ �Ʊ� �ٸ��� ����, 255�� �߸���.
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;


public:
	FORCEINLINE EEnemyType GetEnemyType() { return EnemyType; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	ACEnemy();

	//Actor�� �ִ� TakeDamage�Լ��� �������ؼ� ���
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Hitted();
	void Dead();

private:
	void End_Dead() override;

private:
	struct FDamageData
	{
		float Amount;   //��������
		class ACharacter* Attacker;    //������ ĳ����
		struct FHitDamageEvent* Event;
		//CWeaponStructures�� ���� �������� FHitDamageEvent ����ü
	} Damage;

};
