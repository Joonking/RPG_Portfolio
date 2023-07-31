#include "WeaponDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"

#include "WeaponEquipmentData.h"
#include "SWeaponCheckBoxes.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeaponStructures.h"

#include "Animation/AnimMontage.h"

bool FWeaponDetailsView::RefreshByCheckBoxes = false;

TSharedRef<IDetailCustomization> FWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new FWeaponDetailsView());
}

void FWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Type = UCWeaponAsset::StaticClass();

	//Attachment
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Attachment", FText::FromName("Attachment"));
		category.AddProperty("AttachmentClass", Type);
	}

	//Equipment
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Equipment", FText::FromName("Equipment"));
		IDetailPropertyRow& row = category.AddProperty("EquipmentData", Type);

		if (RefreshByCheckBoxes == false)
		{
			FWeaponEquipmentData::RemoveCheckBoxes();
			TSharedPtr<SWeaponCheckBoxes> checkBoxes = FWeaponEquipmentData::CreateCheckBoxes();

			int32 index = 0;
			checkBoxes->Add("Montage", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("PlayRatio", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("CanMove", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("ControlRotation", row.GetPropertyHandle()->GetChildHandle((uint32)index++));

			index = 0;
			FEquipmentData data;
			checkBoxes->CheckDefaultObject(index++, data.Montage);
			checkBoxes->CheckDefaultValue(index++, data.PlayRatio);
			checkBoxes->CheckDefaultValue(index++, data.bCanMove);
			checkBoxes->CheckDefaultValue(index++, data.bUseControlRotation);
		}
	}

	//DoAction
	{
		//DoAction 카테고리 생성
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("DoAction",
			FText::FromName("DoAction"));
		category.AddProperty("DoActionClass", Type);

		//DoActionDatas 변수명을 가진 데이터 추가 
		IDetailPropertyRow& row = category.AddProperty("DoActionAndHitDatas", Type);
	}

	//Skill
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Skill", FText::FromName("Skill"));
		category.AddProperty("SkillClass_1", Type);
		category.AddProperty("SkillClass_2", Type);
		category.AddProperty("SkillClass_3", Type);
		category.AddProperty("SkillClass_4", Type);
	}

}