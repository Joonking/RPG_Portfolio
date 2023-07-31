#include "AssetTypeActions_Weapon.h"
#include "WeaponAssetEditor.h"
#include "Weapons/CWeaponAsset.h"

FAssetTypeActions_Weapon::FAssetTypeActions_Weapon(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

//에셋 이름 지정
FText FAssetTypeActions_Weapon::GetName() const
{
	return FText::FromString("Weapon Asset");
}

//에셋 클래스 지정
UClass* FAssetTypeActions_Weapon::GetSupportedClass() const
{
	return UCWeaponAsset::StaticClass();
}

//에셋 색깔 지정
FColor FAssetTypeActions_Weapon::GetTypeColor() const
{
	return FColor::Yellow;
}

uint32 FAssetTypeActions_Weapon::GetCategories()
{
	return Category;
}

void FAssetTypeActions_Weapon::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if (InObjects.Num() < 1)
		return;

	FWeaponAssetEditor::OpenWindow(InObjects[0]->GetName());
}