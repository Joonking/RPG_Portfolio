#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CMoveComponent.h"
#include "CBTTaskNode_Speed.generated.h"

UCLASS()
class C_PORTFOLIO_API UCBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()

private:
	//블프에서 설정할 스피드 타입 
	UPROPERTY(EditAnywhere, Category = "Type")
		ESpeedType Type;

public:
	UCBTTaskNode_Speed();

private:
	//UBTTaskNode 부모에 있는 ExecuteTask 함수는 private으로 선언되었지만 
	//자식에서 재정의 가능함.
	//C에서는 불가능한 문법이지만, 언리얼 C에서는 가능함.
	//근데 외부에서 콜할 Execute 함수를 왜 private 으로 선언했을까??
	//이유는 밑에 예시로 따로 적었음. 
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

};
