#include "Characters/CAIController.h"
#include "Global.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/CEnemy.h"
#include "Characters/CPlayer.h"
#include "Components/CAIStateComponent.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");



	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1800;  //시야 감지 반경
	Sight->LoseSightRadius = 2000;  //시야 벗어날 때
	Sight->PeripheralVisionAngleDegrees = 90;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;   //적 만 감지 하겠다.
	Sight->DetectionByAffiliation.bDetectNeutrals = false;  //중립은 감지하지 않겠다. 
	Sight->DetectionByAffiliation.bDetectFriendlies = false;  //아군은 감지하지 않겠다. 

	Perception->ConfigureSense(*Sight);   //SenseConfig 설정. 매개변수에 주소를 받는 이유는
	//여러개가 있다면 배열로 넣으라고 하는거임.

	Perception->SetDominantSense(*Sight->GetSenseImplementation());
	//여러개 있을때 우선순위를 정하는거임. 

}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	//감지했을때 OnPerceptionUpdated 델리게이트 호출 
	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<ACEnemy>(InPawn); //빙의될 컨트롤러 소유자(적 캐릭터) 설정

	//TeamID는 Controller에서 설정함.
	SetGenericTeamId(Enemy->GetTeamID());

	//블랙보드 설정
	UseBlackboard(Enemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	//Enemy로 부터 AIStateComponent 가져옴
	AIState = CHelpers::GetComponent<UCAIStateComponent>(Enemy);
	//AIStateComponent에 Balckboard 넘겨줌
	AIState->SetBlackboard(Blackboard);

	//비헤이비어 트리 실행
	RunBehaviorTree(Enemy->GetBehaviorTree());

}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

//감지했을때
void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//감지된 리스트를 우선 actors에 담아둠.
	TArray<AActor*> actors;
	//GetCurrentlyPerceivedActors는 현재 감지된 액터들을 리턴해줌.
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	//actors에 player가 있는지를 체크 (적끼리 싸워야 하면 ACPlayer가 아닌 Character 로 받아야함)
	ACPlayer* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);

		if (!!player)
			break;
	}

	//블랙보드의 Player 변수에 감지한 player를 넣어줌. 
	Blackboard->SetValueAsObject("Player", player);


}


