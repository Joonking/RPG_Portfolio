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

	//BehaviorTree인 OwnerComp 
	//(Service 입장에서 자신을 소유한건 BehaviorTree라 이름이 이런듯)
	//그러면 BehaviorTree를 소유한애는 Controller임.
	//그래서 OwnerComp.GetOwner 는 비헤이비어 트리를 실행한 Controller임. 
	//이걸 우리가 만든 ACAIController형으로 캐스팅해서 controller에 저장.
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//빙의된 대상은 controller의 GetPawn으로 가져옴. 
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	//ai의 State, AIState 컴포넌트 가져옴. 
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIStateComponent* aiState = CHelpers::GetComponent<UCAIStateComponent>(ai);

	//블프에서는 서비스에서 Hit처리를 하지않았지만 이번엔 여기서 해볼거임.
	//State가 Hitted 모드이면 aiState도 Hitted 모드로 변경시켜줌. 
	if (state->IsHittedMode())
	{
		aiState->SetHittedMode();

		return;
	}

	//AIState로 부터 블랙보드의 PlayerKey 값을 가져와서 player에 넣어줌.
	ACPlayer* player = aiState->GetTargetPlayer();
	if (player == nullptr) //player가 없다면 즉, 인식한 대상이 없으면
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

	//이 아래는 Player를 인식한 상태임.
	//ai와 player 사이의 거리 distance가
	float distance = ai->GetDistanceTo(player);

	//Range_3보다 가까우면 공격
	if (distance < Range_3)
	{
		aiState->SetActionMode();
		return;
	}

	//Range_1보다 멀면 Approach
	aiState->SetApproachMode();

}





