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
	//�������� ������ ���ǵ� Ÿ�� 
	UPROPERTY(EditAnywhere, Category = "Type")
		ESpeedType Type;

public:
	UCBTTaskNode_Speed();

private:
	//UBTTaskNode �θ� �ִ� ExecuteTask �Լ��� private���� ����Ǿ����� 
	//�ڽĿ��� ������ ������.
	//C������ �Ұ����� ����������, �𸮾� C������ ������.
	//�ٵ� �ܺο��� ���� Execute �Լ��� �� private ���� ����������??
	//������ �ؿ� ���÷� ���� ������. 
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

};
