#include "SWeaponCheckBoxes.h"
#include "Widgets/Layout/SScaleBox.h"
#include "IPropertyUtilities.h"
#include "IDetailPropertyRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"

#include "WeaponDetailsView.h"

void SWeaponCheckBoxes::Add(FString InName, TSharedPtr<IPropertyHandle> InHandle)
{
	InternalDatas.Add(FInternalData(InName, InHandle));
}

TSharedRef<SWidget> SWeaponCheckBoxes::Draw()
{
	TSharedPtr<SHorizontalBox> box;
	SAssignNew(box, SHorizontalBox);

	for (int32 i = 0; i < InternalDatas.Num(); i++)
	{
		box->AddSlot()
			.AutoWidth()
			[
				DrawCheckBox(i)
			];
	}

	return box.ToSharedRef();
}

TSharedRef<SWidget> SWeaponCheckBoxes::DrawCheckBox(int32 InIndex)
{
	return SNew(SCheckBox)
		.IsChecked(InternalDatas[InIndex].bChecked)
		.OnCheckStateChanged(this, &SWeaponCheckBoxes::OnCheckStateChanged, InIndex)
		.Content()
		[
			SNew(SScaleBox)
			.Content()
		[
			SNew(STextBlock)
			.Margin(FMargin(0, 0, 10, 0))
		.Text(FText::FromString(InternalDatas[InIndex].Name))
		]
		];
}

void SWeaponCheckBoxes::DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder* InChildBuilder)
{
	for (int32 i = 0; i < InternalDatas.Num(); i++)
	{
		if (InternalDatas[i].bChecked == false)
			continue;

		TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
		IDetailPropertyRow& row = InChildBuilder->AddProperty(handle.ToSharedRef());


		TSharedPtr<SWidget> name;
		TSharedPtr<SWidget> value;

		row.GetDefaultWidgets(name, value);

		row.CustomWidget()
			.NameContent()
			[
				name.ToSharedRef()
			]
		.ValueContent()
			.MinDesiredWidth(300)
			[
				value.ToSharedRef()
			];
	}
}

void SWeaponCheckBoxes::OnCheckStateChanged(ECheckBoxState InState, int32 InIndex)
{
	InternalDatas[InIndex].bChecked = !InternalDatas[InIndex].bChecked;

	FWeaponDetailsView::OnRefresh();
	{
		Utilities->ForceRefresh();
	}
	FWeaponDetailsView::OffRefresh();
}

void SWeaponCheckBoxes::SetUtilities(TSharedPtr<IPropertyUtilities> InUtilities)
{
	Utilities = InUtilities;
}

void SWeaponCheckBoxes::CheckDefaultObject(int32 InIndex, UObject* InValue)
{
	UObject* val = nullptr;
	InternalDatas[InIndex].Handle->GetValue(val);

	if (!!val && InValue != val)
		InternalDatas[InIndex].bChecked = true;
}

void SWeaponCheckBoxes::CheckDefaultValue(int32 InIndex, float InValue)
{
	float val;
	InternalDatas[InIndex].Handle->GetValue(val);

	if (InValue != val)
		InternalDatas[InIndex].bChecked = true;
}

void SWeaponCheckBoxes::CheckDefaultValue(int32 InIndex, bool InValue)
{
	bool val;
	InternalDatas[InIndex].Handle->GetValue(val);

	if (InValue != val)
		InternalDatas[InIndex].bChecked = true;
}

void SWeaponCheckBoxes::CheckDefaultValue(int32 InIndex, const FVector& InValue)
{
	FVector val;
	InternalDatas[InIndex].Handle->GetValue(val);

	if (InValue != val)
		InternalDatas[InIndex].bChecked = true;
}