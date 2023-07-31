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
	//AttachmentClass, DoActionClass �⺻ Ŭ���� ����
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
		//DoAction�� BeginPlay ȣ�����ָ鼭 WeaponAsset�� �����͵� �Ѱ���.
		doAction->BeginPlay(attachment, equipment, InOwner, DoActionAndHitDatas);

		if (!!attachment)
		{
			//������ Collision�� ������ ������, ȣ��� ��������Ʈ�� DoAction�� �ִ� �Լ��� ����
			attachment->OnAttachmentCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &UCDoAction::OffAttachmentCollision);

			//���⿡ ���� �¾�����(Overlap), ȣ��� ��������Ʈ�� DoAction�� �ִ� �Լ��� ����
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

	//������ �����ߴ� �ӽ� �������� ��� WeaponData�� �Ѱ��ִ°���. 
	//WeaponData�� �ϳ� �����ؼ� �Ű������� �־��� ���� OutWeaponData�� �־���. 
	//�̷��� �Ǹ� �Ű������� �־��� ���� ���� WeaponData�� ���� ������ �������� ����.
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

