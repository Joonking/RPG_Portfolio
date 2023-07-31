#include "BehaviorTree/CBTTaskNode_Equip.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Weapons/CEquipment.h"

UCBTTaskNode_Equip::UCBTTaskNode_Equip()
{
	NodeName = "Equip";

	bNotifyTick = true;  //이게 있어야 tick이 동작함. 
}

EBTNodeResult::Type UCBTTaskNode_Equip::ExecuteTask(UBehaviorTreeComponent&
	OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	//ai로 부터 WeaponComponent 가져오기
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	//ai의 현재 Weapon Type이 Equip할 Type과 같으면 장착 할 필요 없으니 성공으로 마무리
	if (Type == weapon->GetType())
		return EBTNodeResult::Succeeded;

	//장착할 타입에 대해 스위치
	switch (Type)
	{
	case EWeaponType::Sword: weapon->SetSwordMode(); break;
	}

	//장착 중인상태로 Execute를 마무리해야하니까 InProgress 상태로 리턴
	return EBTNodeResult::InProgress;
}

//무기 장착이 완료되면 Idle 모드가 됨. Tick에서 Idle 모드인지를 체크해서
//Idle 모드로 변경 되었으면 무기 장착 완료로 끝내려고 사용
void UCBTTaskNode_Equip::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsIdleMode())  //idle 이면
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
