#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentOverlap,
class ACharacter*, InAttacker, class UShapeComponent*,
	InCollision, class ACharacter*, InOther);


UCLASS()
class C_PORTFOLIO_API ACAttachment : public AActor
{
	GENERATED_BODY()

public:
	FAttachmentCollision OnAttachmentCollision;     //OnCollision시에 호출할 델리게이트
	FAttachmentCollision OffAttachmentCollision;    //OffCollision시에 호출할 델리게이트
	//무기의 Collision에 BeginOverlap 되면 호출할 델리게이트
	FAttachmentOverlap OnAttachmentBeginOverlap;



protected:
	//블루프린트에서 Root 밑으로 Collision 컴포넌트를 생성해야 하기에 생성
	//USceneComponent 이하 부터 화면에 배치가 가능함
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Root;

public:
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	//캐릭터의 소켓명을 매개변수로 받아 해당 소켓으로 무기를 붙이는 함수
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachTo(FName InSocketName);

	//캐릭터의 소켓명을 매개변수로 받아 해당 소켓으로 Collision을 붙이는 함수
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachToCollision(class UShapeComponent* InCollision, FName InSocketName);

public:
	//무기 장착시에 무기가 붙은 소켓 위치를 변경하기 위한 함수
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();
	//무기 해제시에 무기가 붙은 소켓 위치를 변경하기 위한 함수
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnEquip();

public:
	void OnCollision();   //무기의 Collision을 활성화 하는 함수
	void OffCollision();  //무기의 Collision을 비활성화 하는 함수

private:
	//Collision에 Begin Overlap 시에 델리게이트에 의해 호출될 함수
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;   //무기 소유자

protected:
	//무기가 가지는 모든 Collision을 담을 배열변수
	TArray<class UShapeComponent*> Collisions;
};
