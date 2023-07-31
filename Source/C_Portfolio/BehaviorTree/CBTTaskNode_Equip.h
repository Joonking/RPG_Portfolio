#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CWeaponComponent.h"
#include "CBTTaskNode_Equip.generated.h"

UCLASS()
class C_PORTFOLIO_API UCBTTaskNode_Equip : public UBTTaskNode
{
	GENERATED_BODY()

private:
	//블프에서 지정해 줄 장착할 무기 타입
	UPROPERTY(EditAnywhere, Category = "Type")
		EWeaponType Type;

public:
	UCBTTaskNode_Equip();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent&
		OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& 
		OwnerComp, uint8* NodeMemory) override;
};
