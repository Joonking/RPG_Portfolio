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
	Sight->SightRadius = 1800;  //�þ� ���� �ݰ�
	Sight->LoseSightRadius = 2000;  //�þ� ��� ��
	Sight->PeripheralVisionAngleDegrees = 90;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;   //�� �� ���� �ϰڴ�.
	Sight->DetectionByAffiliation.bDetectNeutrals = false;  //�߸��� �������� �ʰڴ�. 
	Sight->DetectionByAffiliation.bDetectFriendlies = false;  //�Ʊ��� �������� �ʰڴ�. 

	Perception->ConfigureSense(*Sight);   //SenseConfig ����. �Ű������� �ּҸ� �޴� ������
	//�������� �ִٸ� �迭�� ������� �ϴ°���.

	Perception->SetDominantSense(*Sight->GetSenseImplementation());
	//������ ������ �켱������ ���ϴ°���. 

}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	//���������� OnPerceptionUpdated ��������Ʈ ȣ�� 
	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<ACEnemy>(InPawn); //���ǵ� ��Ʈ�ѷ� ������(�� ĳ����) ����

	//TeamID�� Controller���� ������.
	SetGenericTeamId(Enemy->GetTeamID());

	//������ ����
	UseBlackboard(Enemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	//Enemy�� ���� AIStateComponent ������
	AIState = CHelpers::GetComponent<UCAIStateComponent>(Enemy);
	//AIStateComponent�� Balckboard �Ѱ���
	AIState->SetBlackboard(Blackboard);

	//�����̺�� Ʈ�� ����
	RunBehaviorTree(Enemy->GetBehaviorTree());

}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

//����������
void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//������ ����Ʈ�� �켱 actors�� ��Ƶ�.
	TArray<AActor*> actors;
	//GetCurrentlyPerceivedActors�� ���� ������ ���͵��� ��������.
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	//actors�� player�� �ִ����� üũ (������ �ο��� �ϸ� ACPlayer�� �ƴ� Character �� �޾ƾ���)
	ACPlayer* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);

		if (!!player)
			break;
	}

	//�������� Player ������ ������ player�� �־���. 
	Blackboard->SetValueAsObject("Player", player);


}


