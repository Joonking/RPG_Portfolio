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

	//�����̺�� Ʈ��(OwnerComp)�� ���� Controller�� ��������
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//Controller�� ���� ������ ĳ���� Pawn(ai)�� ��������
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	//ai�� ���� Move ������Ʈ�� ������.
	UCMoveComponent* move = CHelpers::GetComponent<UCMoveComponent>(ai);

	move->SetSpeed(Type);

	//�׽�ũ�� ���� ���θ� �˷���� �������� �Ѿ.
	//���ǵ� �׽�ũ�� Sequence �ȿ��� �ӵ� ���� �����ϰ� �������� �Ѿ�� �ϴϱ�
	// ������ ����
	return EBTNodeResult::Succeeded;
}