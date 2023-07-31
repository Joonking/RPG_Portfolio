#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeaponData.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CEquipment.h"
#include "Weapons/CDoAction.h"
#include "Weapons/CSkill.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	for(int i=0;i<(int32)EWeaponType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(Owner, &Datas[i]);
		//BeginPlay �ÿ� Datas�� Data ������ ���� �����༭
		//�� Data�����ȿ� ��ü���� �������ִ°���. 
	}
}


void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//���� ���� Ÿ�Կ� ���� Attachment�� �������ִ� �Լ�
ACAttachment* UCWeaponComponent::GetAttachment()
{
	//UnarmedMode ��� nullptr ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//DataAssets�� ����Ÿ�Կ� ���� DataAsset�� null�̶�� nullptr ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ���� Ÿ�Կ� ���� Attachment�� ����
	return Datas[(int32)Type]->GetAttachment();
	//DatasAsset�� �ƴ� Datas���� ���� �����ͼ� ���� 
}

//���� ���� Ÿ�Կ� ���� Equipment�� �������ִ� �Լ�
UCEquipment* UCWeaponComponent::GetEquipment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetEquipment();
}

//DataAssets���� ���� ���� Ÿ�Կ� �´� DoAction�� �������� �Լ�
UCDoAction* UCWeaponComponent::GetDoAction()
{
	//Unarmed ����� ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//���� ����Ÿ���� DataAsset�� ������ ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ����Ÿ�Կ� ���� DoAction ����
	return Datas[(int32)Type]->GetDoAction();
}

UCSkill* UCWeaponComponent::GetSkill_1()
{
	//Unarmed ����� ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//���� ����Ÿ���� DataAsset�� ������ ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ����Ÿ�Կ� ���� Skill_1 ����
	return Datas[(int32)Type]->GetSkill_1();
}

UCSkill* UCWeaponComponent::GetSkill_2()
{
	//Unarmed ����� ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//���� ����Ÿ���� DataAsset�� ������ ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ����Ÿ�Կ� ���� Skill_2 ����
	return Datas[(int32)Type]->GetSkill_2();
}

UCSkill* UCWeaponComponent::GetSkill_3()
{
	//Unarmed ����� ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//���� ����Ÿ���� DataAsset�� ������ ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ����Ÿ�Կ� ���� Skill_3 ����
	return Datas[(int32)Type]->GetSkill_3();
}

UCSkill* UCWeaponComponent::GetSkill_4()
{
	//Unarmed ����� ����
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//���� ����Ÿ���� DataAsset�� ������ ����
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//���� ����Ÿ�Կ� ���� Skill_4 ����
	return Datas[(int32)Type]->GetSkill_4();
}


//���� Ÿ�� ���� �Լ�
void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, Type);
}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	//���� ����� �ٲ� ���Ⱑ ������(��������)
	if(Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if(IsUnarmedMode() ==false) //���� ���� �� �̶��
	{
		GetEquipment()->UnEquip();
	}

	//���� Ÿ�Կ� ���� DataAsset�� ������
	if(!!DataAssets[(int32)InType])
	{
		//���� Ÿ�Կ� ���� DataAsset�� Equipment�� ������ Equip ����
		Datas[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);
	}
}

void UCWeaponComponent::SetUnarmedMode()
{
	//GetEquipment�� Equip������ �����ͼ� UnEquip ȣ��
	GetEquipment()->UnEquip();
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetSwordMode()
{
	ClearDoActionIndex();
	SetMode(EWeaponType::Sword);
}

void UCWeaponComponent::SetSpearMode()
{
	ClearDoActionIndex();
	SetMode(EWeaponType::Spear);
}

void UCWeaponComponent::SetBowMode()
{
	SetMode(EWeaponType::Bow);
}

void UCWeaponComponent::SetDaggerMode()
{
	SetMode(EWeaponType::Dagger);
}

void UCWeaponComponent::SetHammerMode()
{
	SetMode(EWeaponType::Hammer);
}

void UCWeaponComponent::SetStaffMode()
{
	SetMode(EWeaponType::Staff);
}

void UCWeaponComponent::SetWarpMode()
{
	SetMode(EWeaponType::Warp);
}

void UCWeaponComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	//DoAction ��ü�� ������ �� ������
	if (!!GetDoAction())
		GetDoAction()->DoAction(DoActionIndex);
}

void UCWeaponComponent::Skill_1_Pressed()
{
	if (!!GetSkill_1())
		GetSkill_1()->Pressed();

	if (OnSkillCoolTime.IsBound())
		OnSkillCoolTime.Broadcast(ESkillType::Skill_1, 5);
}

void UCWeaponComponent::SKill_1_Released()
{
	if (!!GetSkill_1())
		GetSkill_1()->Released();
}

void UCWeaponComponent::Skill_2_Pressed()
{
	if (!!GetSkill_2())
		GetSkill_2()->Pressed();

	if (OnSkillCoolTime.IsBound())
		OnSkillCoolTime.Broadcast(ESkillType::Skill_2, 5);
}

void UCWeaponComponent::SKill_2_Released()
{
	if (!!GetSkill_2())
		GetSkill_2()->Released();
}


void UCWeaponComponent::Skill_3_Pressed()
{
	if (!!GetSkill_3())
		GetSkill_3()->Pressed();

	if (OnSkillCoolTime.IsBound())
		OnSkillCoolTime.Broadcast(ESkillType::Skill_3, 5);
}

void UCWeaponComponent::SKill_3_Released()
{
	if (!!GetSkill_3())
		GetSkill_3()->Released();
}


void UCWeaponComponent::Skill_4_Pressed()
{
	if (!!GetSkill_4())
		GetSkill_4()->Pressed();

	if (OnSkillCoolTime.IsBound())
		OnSkillCoolTime.Broadcast(ESkillType::Skill_4, 100);
}

void UCWeaponComponent::SKill_4_Released()
{
	if (!!GetSkill_4())
		GetSkill_4()->Released();
}


