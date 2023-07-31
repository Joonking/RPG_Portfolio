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
	FAttachmentCollision OnAttachmentCollision;     //OnCollision�ÿ� ȣ���� ��������Ʈ
	FAttachmentCollision OffAttachmentCollision;    //OffCollision�ÿ� ȣ���� ��������Ʈ
	//������ Collision�� BeginOverlap �Ǹ� ȣ���� ��������Ʈ
	FAttachmentOverlap OnAttachmentBeginOverlap;



protected:
	//�������Ʈ���� Root ������ Collision ������Ʈ�� �����ؾ� �ϱ⿡ ����
	//USceneComponent ���� ���� ȭ�鿡 ��ġ�� ������
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Root;

public:
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	//ĳ������ ���ϸ��� �Ű������� �޾� �ش� �������� ���⸦ ���̴� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachTo(FName InSocketName);

	//ĳ������ ���ϸ��� �Ű������� �޾� �ش� �������� Collision�� ���̴� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachToCollision(class UShapeComponent* InCollision, FName InSocketName);

public:
	//���� �����ÿ� ���Ⱑ ���� ���� ��ġ�� �����ϱ� ���� �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();
	//���� �����ÿ� ���Ⱑ ���� ���� ��ġ�� �����ϱ� ���� �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnEquip();

public:
	void OnCollision();   //������ Collision�� Ȱ��ȭ �ϴ� �Լ�
	void OffCollision();  //������ Collision�� ��Ȱ��ȭ �ϴ� �Լ�

private:
	//Collision�� Begin Overlap �ÿ� ��������Ʈ�� ���� ȣ��� �Լ�
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;   //���� ������

protected:
	//���Ⱑ ������ ��� Collision�� ���� �迭����
	TArray<class UShapeComponent*> Collisions;
};
