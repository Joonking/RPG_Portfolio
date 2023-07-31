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

	//End_Dead�� �������� �ʰ� ���������Լ��� ���� �ڽĿ��� ������ ������ �� �ְ� �����
	virtual void End_Dead() = 0;

};
