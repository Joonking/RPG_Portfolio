#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAIStateComponent.generated.h"

UENUM(BlueprintType)
enum class EAIStateType : uint8
{
	Wait = 0, Approach, Action, Patrol, Hitted, Avoid, Stun, Assassin, Strafing, Dead, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateTypeChanged,
	EAIStateType, InPrevType, EAIStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PORTFOLIO_API UCAIStateComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//Black Board의 키 이름들
	//이넘 형식의 EAIStateType을 저장 할 블랙보드의 변수이름과 동일한 이름의 변수
	UPROPERTY(EditAnywhere, Category = "Key")
		FName AIStateTypeKey = "AIStateType";

	//타겟인 플레이어를 저장 할 블랙보드의 변수이름과 동일한 이름의 변수 
	UPROPERTY(EditAnywhere, Category = "Key")
		FName PlayerKey = "Player";

	//Patrol할때 사용할 Location변수이름과 동일한 이름의 변수
	UPROPERTY(EditAnywhere, Category = "Key")
		FName LocationKey = "Location";

public:
	//Controller에서 비헤이비어 트리를 가져오고 거기서 블랙보드를 가져온뒤에
	//여기 AIStateComponent에 넘겨서 Blackboard에 Set 해줌. 그때 사용할 함수 
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard)
		{ Blackboard = InBlackboard;}

public:	
	UCAIStateComponent();

protected:
	virtual void BeginPlay() override;

private:
	//블랙보드의 AIStateTypeKey변수의 값을 가져와서
	// 현재 EAIStateType을 리턴해주는 함수 
	EAIStateType GetType();

public:
	bool IsWaitMode();
	bool IsApproachMode();
	bool IsActionMode();
	bool IsPatrolMode();
	bool IsHittedMode();
	bool IsAvoidMode();
	bool IsStunMode();
	bool IsAssassinMode();
	bool IsStrafingMode();
	bool IsDeadMode();

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();
	void SetStunMode();
	void SetAssassinMode();
	void SetStrafingMode();
	void SetDeadMode();

private:
	void ChangeType(EAIStateType InType);

public:
	class ACPlayer* GetTargetPlayer();
	FVector GetLocation();

public:
	FAIStateTypeChanged OnAIStateTypeChanged;

private:
	class UBlackboardComponent* Blackboard;

};
