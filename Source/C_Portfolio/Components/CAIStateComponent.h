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
	//Black Board�� Ű �̸���
	//�̳� ������ EAIStateType�� ���� �� �������� �����̸��� ������ �̸��� ����
	UPROPERTY(EditAnywhere, Category = "Key")
		FName AIStateTypeKey = "AIStateType";

	//Ÿ���� �÷��̾ ���� �� �������� �����̸��� ������ �̸��� ���� 
	UPROPERTY(EditAnywhere, Category = "Key")
		FName PlayerKey = "Player";

	//Patrol�Ҷ� ����� Location�����̸��� ������ �̸��� ����
	UPROPERTY(EditAnywhere, Category = "Key")
		FName LocationKey = "Location";

public:
	//Controller���� �����̺�� Ʈ���� �������� �ű⼭ �����带 �����µڿ�
	//���� AIStateComponent�� �Ѱܼ� Blackboard�� Set ����. �׶� ����� �Լ� 
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard)
		{ Blackboard = InBlackboard;}

public:	
	UCAIStateComponent();

protected:
	virtual void BeginPlay() override;

private:
	//�������� AIStateTypeKey������ ���� �����ͼ�
	// ���� EAIStateType�� �������ִ� �Լ� 
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
