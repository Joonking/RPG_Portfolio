#pragma once

#include "CoreMinimal.h"

class WEAPON_API SWeaponCheckBoxes
	: public TSharedFromThis<SWeaponCheckBoxes>
{
public:
	void Add(FString InName, TSharedPtr<IPropertyHandle> InHandle);

public:
	void SetUtilities(TSharedPtr<class IPropertyUtilities> InUtilities);

public:
	TSharedRef<class SWidget> Draw();

private:
	TSharedRef<class SWidget> DrawCheckBox(int32 InIndex);

public:
	void DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder* InChildBuilder);

private:
	void OnCheckStateChanged(ECheckBoxState InState, int32 InIndex);

public:
	void CheckDefaultObject(int32 InIndex, UObject* InValue);
	void CheckDefaultValue(int32 InIndex, float InValue);
	void CheckDefaultValue(int32 InIndex, bool InValue);
	void CheckDefaultValue(int32 InIndex, const FVector& InValue);

private:
	TSharedPtr<class IPropertyUtilities> Utilities;

private:
	struct FInternalData
	{
		bool bChecked;
		FString Name;
		TSharedPtr<IPropertyHandle> Handle;

		FInternalData()
		{

		}

		FInternalData(FString InName, TSharedPtr<IPropertyHandle> InHandle)
		{
			bChecked = false;
			Name = InName;
			Handle = InHandle;
		}
	};
	TArray<FInternalData> InternalDatas;
};
