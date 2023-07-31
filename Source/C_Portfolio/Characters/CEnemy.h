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

	//블프에서는 못하지만 C에서는 Team을 명시해줄 수 있음.
	//TeamID가 같으면 아군 다르면 적군, 255는 중립임.
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;


public:
	FORCEINLINE EEnemyType GetEnemyType() { return EnemyType; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	ACEnemy();

	//Actor에 있는 TakeDamage함수를 재정의해서 사용
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
		float Amount;   //데미지량
		class ACharacter* Attacker;    //공격한 캐릭터
		struct FHitDamageEvent* Event;
		//CWeaponStructures에 따로 만들어줬던 FHitDamageEvent 구조체
	} Damage;

};
