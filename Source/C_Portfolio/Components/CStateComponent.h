#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle = 0, Backstep, Roll, Equip, Action, Skill, Parkour, Hitted, Stun, Assassin, Dead, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom))
class C_PORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == EStateType::Backstep; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSkillMode() { return Type == EStateType::Skill; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsParkourMode() { return Type == EStateType::Parkour; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStunMode() { return Type == EStateType::Stun; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsAssassinMode() { return Type == EStateType::Assassin; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void SetIdleMode();

	UFUNCTION(BlueprintCallable)
		void SetBackstepMode();

	UFUNCTION(BlueprintCallable)
		void SetRollMode();

	UFUNCTION(BlueprintCallable)
		void SetEquipMode();

	UFUNCTION(BlueprintCallable)
		void SetActionMode();

	UFUNCTION(BlueprintCallable)
		void SetSkillMode();

	UFUNCTION(BlueprintCallable)
		void SetParkourMode();

	UFUNCTION(BlueprintCallable)
		void SetHittedMode();

	UFUNCTION(BlueprintCallable)
		void SetStunMode();

	UFUNCTION(BlueprintCallable)
		void SetAssassinMode();

	UFUNCTION(BlueprintCallable)
		void SetDeadMode();

private:
	void ChangeType(EStateType InType);

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type;
		
};
