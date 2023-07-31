#include "BehaviorTree/CBTTaskNode_Hitted.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"


UCBTTaskNode_Hitted::UCBTTaskNode_Hitted()
{
	NodeName = "Hitted";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Hitted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	controller->StopMovement();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Hitted::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsHittedMode() == false)
	{
		//Hitted Mode가 아니고 Wait Mode로 바뀐거면 빠져나왔다는거니까 성공으로 돌려주기
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}
