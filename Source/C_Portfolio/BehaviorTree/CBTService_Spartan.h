#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Spartan.generated.h"

UCLASS()
class C_PORTFOLIO_API UCBTService_Spartan : public UBTService
{
	GENERATED_BODY()

private:
	//Range는 플레이와의 거리를 나타냄.
	//추격 범위 Range1 넘으면 추격
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_1 = 700;
	//Strafe 범위 Range 1 ~ 2 사이라면 서성이기
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_2 = 300;
	//공격 범위 Range 2 ~ 3 사이라면 공격하러 다가오기
	//Range 3 내외 라면 공격
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_3 = 160;


public:
	UCBTService_Spartan();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;


};
