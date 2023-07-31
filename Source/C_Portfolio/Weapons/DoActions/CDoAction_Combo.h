#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Combo.generated.h"

UCLASS(Blueprintable)
class C_PORTFOLIO_API UCDoAction_Combo : public UCDoAction
{
	GENERATED_BODY()

public:
	//�޺� ������ ��Ÿ���� ���� bEnable�� Ű�� ���� �ζ��� �Լ�
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	void DoAction(int32 InDatasIndex) override;
	void Begin_DoAction() override;
	void End_DoAction() override;

public:
	//Collision�� Off �ɶ� ȣ��� �Լ� ������
	void OffAttachmentCollision() override;

	void OnAttachmentBeginOverlap(ACharacter* InAttacker, UShapeComponent* InCollision, ACharacter* InOther) override;


private:
	//���° ���������� ��Ÿ�� Index
	int32 Index;

	//�����޺� ���������� ��Ÿ�� Enable
	bool bEnable;
	//�޺��������� �Է��� �Ǿ������� ��Ÿ�� Exist
	bool bExist;

	//���⿡ �´� ĳ���͵��� ���� ĳ���� �迭 ����
	TArray<class ACharacter*> HittedCharacters;

	int32 Index_Enemy_Max;


};



