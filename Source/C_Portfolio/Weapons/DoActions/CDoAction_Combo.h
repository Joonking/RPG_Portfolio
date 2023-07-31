#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Combo.generated.h"

UCLASS(Blueprintable)
class C_PORTFOLIO_API UCDoAction_Combo : public UCDoAction
{
	GENERATED_BODY()

public:
	//콤보 구간을 나타내기 위해 bEnable을 키고 끄는 인라인 함수
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	void DoAction(int32 InDatasIndex) override;
	void Begin_DoAction() override;
	void End_DoAction() override;

public:
	//Collision이 Off 될때 호출될 함수 재정의
	void OffAttachmentCollision() override;

	void OnAttachmentBeginOverlap(ACharacter* InAttacker, UShapeComponent* InCollision, ACharacter* InOther) override;


private:
	//몇번째 공격인지를 나타낼 Index
	int32 Index;

	//현재콤보 구간인지를 나타낼 Enable
	bool bEnable;
	//콤보구간에서 입력이 되었는지를 나타낼 Exist
	bool bExist;

	//무기에 맞는 캐릭터들을 담을 캐릭터 배열 변수
	TArray<class ACharacter*> HittedCharacters;

	int32 Index_Enemy_Max;


};



