#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class WEAPON_API FWeaponEquipmentData
	: public IPropertyTypeCustomization
{

public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//üũ�ڽ� �����Լ�
	static TSharedPtr<class SWeaponCheckBoxes> CreateCheckBoxes();
	//üũ�ڽ� ����� �Լ�
	static void RemoveCheckBoxes();

public:
	//�θ��� ���������Լ� ������
	void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;
	void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;

private:
	//üũ �ڽ��� �������� ����� �Ŵϱ� static���� ����.
	static TSharedPtr<class SWeaponCheckBoxes> CheckBoxes;
};