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
		//BeginPlay 시에 Datas의 Data 공간을 같이 보내줘서
		//이 Data공간안에 객체들을 생성해주는거임. 
	}
}


void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//현재 무기 타입에 대한 Attachment를 리턴해주는 함수
ACAttachment* UCWeaponComponent::GetAttachment()
{
	//UnarmedMode 라면 nullptr 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//DataAssets에 현재타입에 대한 DataAsset이 null이라면 nullptr 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기 타입에 대한 Attachment를 리턴
	return Datas[(int32)Type]->GetAttachment();
	//DatasAsset이 아닌 Datas에서 값을 가져와서 수행 
}

//현재 무기 타입에 대한 Equipment를 리턴해주는 함수
UCEquipment* UCWeaponComponent::GetEquipment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetEquipment();
}

//DataAssets에서 현재 무기 타입에 맞는 DoAction을 가져오는 함수
UCDoAction* UCWeaponComponent::GetDoAction()
{
	//Unarmed 모드라면 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//현재 무기타입의 DataAsset이 없으면 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기타입에 대한 DoAction 리턴
	return Datas[(int32)Type]->GetDoAction();
}

UCSkill* UCWeaponComponent::GetSkill_1()
{
	//Unarmed 모드라면 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//현재 무기타입의 DataAsset이 없으면 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기타입에 대한 Skill_1 리턴
	return Datas[(int32)Type]->GetSkill_1();
}

UCSkill* UCWeaponComponent::GetSkill_2()
{
	//Unarmed 모드라면 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//현재 무기타입의 DataAsset이 없으면 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기타입에 대한 Skill_2 리턴
	return Datas[(int32)Type]->GetSkill_2();
}

UCSkill* UCWeaponComponent::GetSkill_3()
{
	//Unarmed 모드라면 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//현재 무기타입의 DataAsset이 없으면 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기타입에 대한 Skill_3 리턴
	return Datas[(int32)Type]->GetSkill_3();
}

UCSkill* UCWeaponComponent::GetSkill_4()
{
	//Unarmed 모드라면 리턴
	CheckTrueResult(IsUnarmedMode(), nullptr);
	//현재 무기타입의 DataAsset이 없으면 리턴
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	//현재 무기타입에 대한 Skill_4 리턴
	return Datas[(int32)Type]->GetSkill_4();
}


//무기 타입 변경 함수
void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, Type);
}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	//현재 무기랑 바꿀 무기가 같을때(무기해제)
	if(Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if(IsUnarmedMode() ==false) //무기 장착 중 이라면
	{
		GetEquipment()->UnEquip();
	}

	//들어온 타입에 대한 DataAsset이 있으면
	if(!!DataAssets[(int32)InType])
	{
		//들어온 타입에 대한 DataAsset에 Equipment를 가져와 Equip 실행
		Datas[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);
	}
}

void UCWeaponComponent::SetUnarmedMode()
{
	//GetEquipment로 Equip데이터 가져와서 UnEquip 호출
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

	//DoAction 객체를 가져올 수 있으면
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


