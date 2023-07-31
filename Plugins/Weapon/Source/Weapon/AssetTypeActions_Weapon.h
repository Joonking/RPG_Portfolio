#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class WEAPON_API FAssetTypeActions_Weapon
	: public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_Weapon(EAssetTypeCategories::Type InCategory);

	//�θ� FAssetTypeActions_Base�� �ִ� ���� �����Լ��� ������
	virtual FText GetName() const override;   //��Ÿ�� �����̸�. 
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	uint32 GetCategories() override;

public:
	void OpenAssetEditor(const TArray<UObject*>& InObjects,
		TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>());

private:
	EAssetTypeCategories::Type Category;    //���ο� ī�װ�
};