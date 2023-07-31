#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamaged, float, NewHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateMP, float, NewMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuff);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOffBuff);


UCLASS( ClassGroup=(Custom))
class C_PORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
		float MaxHP = 100;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
		float HP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MP")
		float MaxMP = 100;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MP")
		float MP = 0;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FDamaged OnDamaged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FUpdateMP OnUpdateMP;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FOnBuff OnBuff;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FOffBuff OffBuff;



public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBuffMode() { return BuffMode; }

public:
	FORCEINLINE float GetHealth() { return HP; }
	FORCEINLINE float GetMaxHealth() { return MaxHP; }


public:
	UCStatusComponent();

public:
	void Damage(float InAmount);
	bool CheckSkillMP(float InMP);
	void UpdateMP(float InMP);

public:
	void OnBuffMode();
	void OffBuffMode();

protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;

private:
	bool BuffMode;
	
};
