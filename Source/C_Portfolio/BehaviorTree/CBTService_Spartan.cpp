#include "BehaviorTree/CBTService_Spartan.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Components/CAIStateComponent.h"
#include "Components/CPatrolComponent.h"

UCBTService_Spartan::UCBTService_Spartan()
{
	NodeName = "Spartan";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Spartan::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//BehaviorTree�� OwnerComp 
	//(Service ���忡�� �ڽ��� �����Ѱ� BehaviorTree�� �̸��� �̷���)
	//�׷��� BehaviorTree�� �����Ѿִ� Controller��.
	//�׷��� OwnerComp.GetOwner �� �����̺�� Ʈ���� ������ Controller��. 
	//�̰� �츮�� ���� ACAIController������ ĳ�����ؼ� controller�� ����.
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//���ǵ� ����� controller�� GetPawn���� ������. 
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	//ai�� State, AIState ������Ʈ ������. 
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIStateComponent* aiState = CHelpers::GetComponent<UCAIStateComponent>(ai);

	//���������� ���񽺿��� Hitó���� �����ʾ����� �̹��� ���⼭ �غ�����.
	//State�� Hitted ����̸� aiState�� Hitted ���� ���������. 
	if (state->IsHittedMode())
	{
		aiState->SetHittedMode();

		return;
	}

	//AIState�� ���� �������� PlayerKey ���� �����ͼ� player�� �־���.
	ACPlayer* player = aiState->GetTargetPlayer();
	if (player == nullptr) //player�� ���ٸ� ��, �ν��� ����� ������
	{
		UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);
		if (!!patrol)
		{
			aiState->SetPatrolMode();

			return;
		}

		aiState->SetWaitMode();

		return;
	}

	//�� �Ʒ��� Player�� �ν��� ������.
	//ai�� player ������ �Ÿ� distance��
	float distance = ai->GetDistanceTo(player);

	//Range_3���� ������ ����
	if (distance < Range_3)
	{
		aiState->SetActionMode();
		return;
	}

	//Range_1���� �ָ� Approach
	aiState->SetApproachMode();

}





