#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};


class C_PORTFOLIO_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(class ACharacter* InCharacter, FLinearColor InColor);

	//End_Dead는 정의하지 않고 순수가상함수로 만들어서 자식에서 무조건 정의할 수 있게 만들기
	virtual void End_Dead() = 0;

};
