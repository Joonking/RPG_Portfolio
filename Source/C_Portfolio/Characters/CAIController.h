#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class C_PORTFOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

public:
	ACAIController();

protected:
	virtual void BeginPlay() override;

protected:
	//빙의가 될때 호출 되는 OnPossess
	virtual void OnPossess(APawn* InPawn) override;
	//빙의가 해제될때 호출되는 OnUnPossess
	virtual void OnUnPossess() override;

public:
	//OnPerceptionUpdate 델리게이트에 연결할 함수 
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
	class ACEnemy* Enemy;
	//Perception 방식 시야 Sight
	class UAISenseConfig_Sight* Sight;
	class UCAIStateComponent* AIState;

};
