#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class C_PORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
		EWeaponType WeaponType = EWeaponType::Max;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	class ACharacter* Owner;

};








