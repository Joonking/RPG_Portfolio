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
	//밑에 변수들은 모두 private으로 다른곳에서 접근이 불가능하게 막아둘거임.
	//하지만 WeaponAsset에서 만큼은 접근을 허용하고 싶음. 이럴때 사용하는게 friend 키워드.
	//WeaponAsset 쪽에서 WeaponData를 friend로 선언해도 동일한 효과가 있지만
	//열어주는 쪽에서 friend를 선언하는게 헷갈리지 않음.
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





