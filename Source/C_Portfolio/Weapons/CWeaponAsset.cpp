#include "Weapons/CWeaponAsset.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquipment.h"
#include "CDoAction.h"
#include "CSkill.h"
#include "CWeaponData.h"
#include "GameFramework/Character.h"

UCWeaponAsset::UCWeaponAsset()
{
	//AttachmentClass, DoActionClass 기본 클래스 지정
	AttachmentClass = ACAttachment::StaticClass();
	DoActionClass = UCDoAction::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner, UCWeaponData** OutWeaponData)
{
	//Attachment ------------------------------------------------------------
	ACAttachment* attachment = nullptr;
	if(!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);

	}

	UCEquipment* equipment = NewObject<UCEquipment>(this);
	equipment->BeginPlay(InOwner, EquipmentData);

	if(!!attachment)
	{
		equipment->OnBeginEquip.AddDynamic(attachment, &ACAttachment::OnBeginEquip);
		equipment->OnUnEquip.AddDynamic(attachment, &ACAttachment::OnUnEquip);
	}
	// -----------------------------------------------------------------------------------

	//DoAction ------------------------------------------------------------------------
	UCDoAction* doAction = nullptr;
	if(!!DoActionClass)
	{
		doAction = NewObject<UCDoAction>(this, DoActionClass);
		//DoAction의 BeginPlay 호출해주면서 WeaponAsset의 데이터들 넘겨줌.
		doAction->BeginPlay(attachment, equipment, InOwner, DoActionAndHitDatas);

		if (!!attachment)
		{
			//무기의 Collision이 켜지고 꺼질때, 호출될 델리게이트와 DoAction에 있는 함수들 연결
			attachment->OnAttachmentCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &UCDoAction::OffAttachmentCollision);

			//무기에 적이 맞았을때(Overlap), 호출될 델리게이트와 DoAction에 있는 함수들 연결
			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentBeginOverlap);
		}
	}
	// -----------------------------------------------------------------------------------

	//Skills------------------------------------------------------------------------------
	UCSkill* skill_1 = nullptr;
	UCSkill* skill_2 = nullptr;
	UCSkill* skill_3 = nullptr;
	UCSkill* skill_4 = nullptr;
	if(!!SkillClass_1)
	{
		skill_1 = NewObject<UCSkill>(this, SkillClass_1);
		skill_1->BeginPlay(InOwner);
	}
	if (!!SkillClass_2)
	{
		skill_2 = NewObject<UCSkill>(this, SkillClass_2);
		skill_2->BeginPlay(InOwner);
	}
	if (!!SkillClass_3)
	{
		skill_3 = NewObject<UCSkill>(this, SkillClass_3);
		skill_3->BeginPlay(InOwner);
	}
	if (!!SkillClass_4)
	{
		skill_4 = NewObject<UCSkill>(this, SkillClass_4);
		skill_4->BeginPlay(InOwner);
	}
	// -----------------------------------------------------------------------------------

	//위에서 생성했던 임시 변수들을 모두 WeaponData에 넘겨주는거임. 
	//WeaponData를 하나 생성해서 매개변수로 넣어준 공간 OutWeaponData에 넣어줌. 
	//이렇게 되면 매개변수로 넣어준 공간 마다 WeaponData가 따로 생성됨 공유되지 않음.
	*OutWeaponData = NewObject<UCWeaponData>();
	(*OutWeaponData)->Attachment = attachment;
	(*OutWeaponData)->Equipment = equipment;
	(*OutWeaponData)->DoAction = doAction;
	(*OutWeaponData)->Skill_1 = skill_1;
	(*OutWeaponData)->Skill_2 = skill_2;
	(*OutWeaponData)->Skill_3 = skill_3;
	(*OutWeaponData)->Skill_4 = skill_4;
}


#if WITH_EDITOR
void UCWeaponAsset::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	CheckTrue(FApp::IsGame());

	bool bRefresh = false;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("DoActionDatas") == 0;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0;

	CheckFalse(bRefresh);


	bool bCheck = false;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;

	CheckFalse(bCheck);


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>
		("PropertyEditor");
	TSharedPtr<IDetailsView> detailsView = prop.FindDetailView("WeaponAssetEditorDetailsView");

	if (detailsView.IsValid())
		detailsView->ForceRefresh();
}
#endif

