#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Boss.generated.h"

UCLASS()
class C_PORTFOLIO_API UCBTService_Boss : public UBTService
{
	GENERATED_BODY()

private:
	//Range는 플레이와의 거리를 나타냄.
	//Range 거리 내라면 공격
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range = 200;

public:
	UCBTService_Boss();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;

};
