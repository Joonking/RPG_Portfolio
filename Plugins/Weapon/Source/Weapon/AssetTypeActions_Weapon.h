#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class WEAPON_API FAssetTypeActions_Weapon
	: public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_Weapon(EAssetTypeCategories::Type InCategory);

	//부모 FAssetTypeActions_Base에 있는 순수 가상함수들 재정의
	virtual FText GetName() const override;   //나타날 에셋이름. 
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	uint32 GetCategories() override;

public:
	void OpenAssetEditor(const TArray<UObject*>& InObjects,
		TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>());

private:
	EAssetTypeCategories::Type Category;    //새로운 카테고리
};