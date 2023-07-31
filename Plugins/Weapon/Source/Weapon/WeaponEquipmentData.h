#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class WEAPON_API FWeaponEquipmentData
	: public IPropertyTypeCustomization
{

public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//체크박스 생성함수
	static TSharedPtr<class SWeaponCheckBoxes> CreateCheckBoxes();
	//체크박스 지우는 함수
	static void RemoveCheckBoxes();

public:
	//부모의 순수가상함수 재정의
	void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;
	void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;

private:
	//체크 박스는 공통으로 사용할 거니까 static으로 선언.
	static TSharedPtr<class SWeaponCheckBoxes> CheckBoxes;
};