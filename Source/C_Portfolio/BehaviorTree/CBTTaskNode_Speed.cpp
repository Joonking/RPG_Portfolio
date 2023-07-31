#include "BehaviorTree/CBTTaskNode_Speed.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "Characters/CAIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent&
	OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//비헤이비어 트리(OwnerComp)로 부터 Controller를 가져오고
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//Controller로 부터 빙의한 캐릭터 Pawn(ai)을 가져오고
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	//ai로 부터 Move 컴포넌트를 가져옴.
	UCMoveComponent* move = CHelpers::GetComponent<UCMoveComponent>(ai);

	move->SetSpeed(Type);

	//테스크의 성공 여부를 알려줘야 다음으로 넘어감.
	//스피드 테스크는 Sequence 안에서 속도 설정 성공하고 다음으로 넘어가야 하니까
	// 성공을 리턴
	return EBTNodeResult::Succeeded;
}