#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Spartan.generated.h"

UCLASS()
class C_PORTFOLIO_API UCBTService_Spartan : public UBTService
{
	GENERATED_BODY()

private:
	//Range�� �÷��̿��� �Ÿ��� ��Ÿ��.
	//�߰� ���� Range1 ������ �߰�
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_1 = 700;
	//Strafe ���� Range 1 ~ 2 ���̶�� �����̱�
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_2 = 300;
	//���� ���� Range 2 ~ 3 ���̶�� �����Ϸ� �ٰ�����
	//Range 3 ���� ��� ����
	UPROPERTY(EditAnywhere, Category = "Range")
		float Range_3 = 160;


public:
	UCBTService_Spartan();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;


};
