#include "WeaponEquipmentData.h"
#include "DetailWidgetRow.h"
#include "SWeaponCheckBoxes.h"

//공통으로 사용할 변수 CheckBoxes nullptr로 초기화. 
//(static 변수니까 외부에서 초기화)
TSharedPtr<class SWeaponCheckBoxes> FWeaponEquipmentData::CheckBoxes = nullptr;

TSharedRef<IPropertyTypeCustomization> FWeaponEquipmentData::MakeInstance()
{
	return MakeShareable(new FWeaponEquipmentData());
}

TSharedPtr<SWeaponCheckBoxes> FWeaponEquipmentData::CreateCheckBoxes()
{
	return CheckBoxes = MakeShareable(new SWeaponCheckBoxes());
}

void FWeaponEquipmentData::RemoveCheckBoxes()
{
	if (CheckBoxes.IsValid())
	{
		CheckBoxes.Reset();
		CheckBoxes = nullptr;
	}
}

void FWeaponEquipmentData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->SetUtilities(InCustomizationUtils.GetPropertyUtilities());  //유틸리티를 CheckBoxes에 넘겨줌.  

	InHeaderRow
		.DiffersFromDefault(false)
		.NameContent() //제목 영역
		[
			InPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent() //내용 영역
		[
			CheckBoxes->Draw()
		];
}

void FWeaponEquipmentData::CustomizeChildren(TSharedRef<IPropertyHandle>
	InPropertyHandle, IDetailChildrenBuilder& InChildBuilder,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->DrawProperties(InPropertyHandle, &InChildBuilder);
}