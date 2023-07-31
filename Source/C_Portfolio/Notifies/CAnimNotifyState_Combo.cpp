#include "Notifies/CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CDoAction.h"
#include "Weapons/DoActions/CDoAction_Combo.h"



FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//1. 노티파이 소유자를 가져온다.
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//2. 소유자가 가진 WeaponComponent를 가져온다.
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);
	CheckNull(weapon->GetDoAction());

	//3. WeaponComponent로 부터 현재 무기타입에 대한 DoAction 객체를 가져온다. (현재 무기타입의 DataAsset에 가서 DoAction을 가져옴)
	//4. 가져온 DoAction객체를 UCDoAction_Combo로 다운캐스팅해준다.
	UCDoAction_Combo* combo = Cast<UCDoAction_Combo>(weapon->GetDoAction());
	CheckNull(combo);

	//4. DoAction_Combo한테 Enable_Combo로 bEnable을 키라고 요청한다.
	combo->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);
	CheckNull(weapon->GetDoAction());

	UCDoAction_Combo* combo = Cast<UCDoAction_Combo>(weapon->GetDoAction());
	CheckNull(combo);

	combo->DisableCombo();
}


