#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSkill.h"
#include "Weapons/CWeaponStructures.h"
#include "CSkill_Buff.generated.h"

UCLASS(Blueprintable)
class C_PORTFOLIO_API UCSkill_Buff : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FDoActionData ActionData;

public:
	void Pressed() override;
	

};
