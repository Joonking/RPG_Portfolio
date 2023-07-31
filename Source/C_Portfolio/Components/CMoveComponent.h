#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMoveComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Stop = 0, Walk, Run, Sprint, Max,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class C_PORTFOLIO_API UCMoveComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 0, 150, 300, 600 };

	UPROPERTY(EditAnywhere, Category = "Mouse")
		FVector2D MouseSpeed = FVector2D(45, 45);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE void Move() { bCanMove = true; }
	FORCEINLINE void Stop() { bCanMove = false; }

public:
	UCMoveComponent();

protected:
	virtual void BeginPlay() override;

public:
	//앞 뒤로 이동함수
	void OnMoveForward(float InAxis);
	//좌 우로 이동함수
	void OnMoveRight(float InAxis);
	//마우스 좌 우
	void OnHorizontalLook(float InAxis);
	//마우스 상 하
	void OnVerticlaLook(float InAxis);

public:
	//Speed 설정 함수
	void SetSpeed(ESpeedType InType);

public:
	//카메라 고정
	UFUNCTION(BlueprintCallable)
		void EnableControlRotation();
	//사방팔방
	UFUNCTION(BlueprintCallable)
		void DisableControlRotation();

private:
	class ACharacter* Owner;

private:
	bool bCanMove = true;

};
