#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSkill.generated.h"

UCLASS(Abstract)
class C_PORTFOLIO_API UCSkill : public UObject
{
	GENERATED_BODY()

public:
	UCSkill();

public:
	virtual void BeginPlay(class ACharacter* InOwner);

public:
	virtual void Pressed();
	virtual void Released();

protected:
	class ACharacter* Owner;

	class UCMoveComponent* Move;
	class UCStatusComponent* Status;
	class UCStateComponent* State;
	class UCWeaponComponent* Weapon;
	

};
