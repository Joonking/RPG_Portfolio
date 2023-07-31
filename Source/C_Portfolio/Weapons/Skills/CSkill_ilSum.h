#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSkill.h"
#include "Weapons/CWeaponStructures.h"
#include "CSkill_ilSum.generated.h"

UCLASS(Blueprintable)
class C_PORTFOLIO_API UCSkill_ilSum : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FDoActionData ActionData_Sword;

	UPROPERTY(EditAnywhere)
		FHitData HitData_Sword;

	UPROPERTY(EditAnywhere)
		FDoActionData ActionData_Spear;

	UPROPERTY(EditAnywhere)
		FHitData HitData_Spear;

public:
	virtual void Pressed() override;

};
