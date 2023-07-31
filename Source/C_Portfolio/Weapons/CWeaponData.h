#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CWeaponData.generated.h"

UCLASS()
class C_PORTFOLIO_API UCWeaponData : public UObject
{
	GENERATED_BODY()

public:
	//�ؿ� �������� ��� private���� �ٸ������� ������ �Ұ����ϰ� ���ƵѰ���.
	//������ WeaponAsset���� ��ŭ�� ������ ����ϰ� ����. �̷��� ����ϴ°� friend Ű����.
	//WeaponAsset �ʿ��� WeaponData�� friend�� �����ص� ������ ȿ���� ������
	//�����ִ� �ʿ��� friend�� �����ϴ°� �򰥸��� ����.
	friend class UCWeaponAsset;

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCSkill* GetSkill_1() { return Skill_1; }
	FORCEINLINE class UCSkill* GetSkill_2() { return Skill_2; }
	FORCEINLINE class UCSkill* GetSkill_3() { return Skill_3; }
	FORCEINLINE class UCSkill* GetSkill_4() { return Skill_4; }

private:
	UPROPERTY()
		class ACAttachment* Attachment;

	UPROPERTY()
		class UCEquipment* Equipment;

	UPROPERTY()
		class UCDoAction* DoAction;

	UPROPERTY()
		class UCSkill* Skill_1;

	UPROPERTY()
		class UCSkill* Skill_2;

	UPROPERTY()
		class UCSkill* Skill_3;

	UPROPERTY()
		class UCSkill* Skill_4;

};





