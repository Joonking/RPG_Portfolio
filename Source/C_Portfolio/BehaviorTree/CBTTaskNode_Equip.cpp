#include "BehaviorTree/CBTTaskNode_Equip.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Weapons/CEquipment.h"

UCBTTaskNode_Equip::UCBTTaskNode_Equip()
{
	NodeName = "Equip";

	bNotifyTick = true;  //�̰� �־�� tick�� ������. 
}

EBTNodeResult::Type UCBTTaskNode_Equip::ExecuteTask(UBehaviorTreeComponent&
	OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	//ai�� ���� WeaponComponent ��������
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	//ai�� ���� Weapon Type�� Equip�� Type�� ������ ���� �� �ʿ� ������ �������� ������
	if (Type == weapon->GetType())
		return EBTNodeResult::Succeeded;

	//������ Ÿ�Կ� ���� ����ġ
	switch (Type)
	{
	case EWeaponType::Sword: weapon->SetSwordMode(); break;
	}

	//���� ���λ��·� Execute�� �������ؾ��ϴϱ� InProgress ���·� ����
	return EBTNodeResult::InProgress;
}

//���� ������ �Ϸ�Ǹ� Idle ��尡 ��. Tick���� Idle ��������� üũ�ؼ�
//Idle ���� ���� �Ǿ����� ���� ���� �Ϸ�� �������� ���
void UCBTTaskNode_Equip::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsIdleMode())  //idle �̸�
	{
		//
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}

EBTNodeResult::Type UCBTTaskNode_Equip::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	//CheckNullResult(weapon, EBTNodeResult::Failed);
	if (weapon == nullptr)
	{
		FinishLatentAbort(OwnerComp); 
		return EBTNodeResult::Failed;
	}

	bool bBegin = weapon->GetEquipment()->GetBeginEquip();
	if (bBegin == false)
		weapon->GetEquipment()->Begin_Equip();
	else
		weapon->GetEquipment()->End_Equip();

	FinishLatentAbort(OwnerComp);
	return EBTNodeResult::Succeeded;

}
