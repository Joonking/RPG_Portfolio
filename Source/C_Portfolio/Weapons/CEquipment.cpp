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

	//������ �������� ����
	if (Data.bCanMove == false)
		Move->Stop();

	//���� �Ŀ� ī�޶� ��������
	if (Data.bUseControlRotation)
		Move->EnableControlRotation();

	if(!!Data.Montage)  //���� ��Ÿ�ְ� ������ 
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRatio);
	}
	else  //���� ��Ÿ�ְ� ������ ���Ƿ� Begin�� End�� ������.
	{
		Begin_Equip();
		End_Equip();
	}

}

//���� ����
void UCEquipment::Begin_Equip()
{
	bBeginEquip = true;  //Begin�� ���Դ����� üũ�ϱ� ���� ����

	//Begin �ÿ� ���� �͵� ��������Ʈ�� ������.
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

//������ �Ϸ�Ǿ�����
void UCEquipment::End_Equip()
{
	bBeginEquip = false;
	bEquipped = true;

	State->SetIdleMode();
	Move->Move();
}

//���� ����
void UCEquipment::UnEquip()
{
	bEquipped = false;
	Move->DisableControlRotation();

	//���� �����Ҷ� ���� �͵� ������.
	if (OnUnEquip.IsBound())
		OnUnEquip.Broadcast();
}




















