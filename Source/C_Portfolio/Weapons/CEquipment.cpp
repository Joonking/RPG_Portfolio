#include "Weapons/CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMoveComponent.h"
#include "Components/CStateComponent.h"

void UCEquipment::BeginPlay(ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	Data = InData;

	Move = CHelpers::GetComponent<UCMoveComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}

void UCEquipment::Equip()
{
	State->SetEquipMode();

	//장착시 움직일지 말지
	if (Data.bCanMove == false)
		Move->Stop();

	//장착 후에 카메라 고정할지
	if (Data.bUseControlRotation)
		Move->EnableControlRotation();

	if(!!Data.Montage)  //장착 몽타주가 있으면 
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRatio);
	}
	else  //장착 몽타주가 없으면 임의로 Begin과 End를 콜해줌.
	{
		Begin_Equip();
		End_Equip();
	}

}

//장착 시작
void UCEquipment::Begin_Equip()
{
	bBeginEquip = true;  //Begin에 들어왔는지를 체크하기 위해 켜줌

	//Begin 시에 콜할 것들 델리게이트로 콜해줌.
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

//장착이 완료되었을때
void UCEquipment::End_Equip()
{
	bBeginEquip = false;
	bEquipped = true;

	State->SetIdleMode();
	Move->Move();
}

//장착 해제
void UCEquipment::UnEquip()
{
	bEquipped = false;
	Move->DisableControlRotation();

	//장착 해제할때 콜할 것들 콜해줌.
	if (OnUnEquip.IsBound())
		OnUnEquip.Broadcast();
}




















