#include "Components/CStatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	HP = MaxHP;
}

void UCStatusComponent::Damage(float InAmount)
{
	HP += (InAmount * -1.0f);
	//양수의 데미지값을 매개변수로 넣어주고, 
	//내부에서 뺄때 -값을 붙이려고 -1을 곱해줌.

	HP = FMath::Clamp(HP, 0.0f, MaxHP);

	//데미지 받았을때 호출해줄 델리게이트
	if (OnDamaged.IsBound())
		OnDamaged.Broadcast(HP);
}

bool UCStatusComponent::CheckSkillMP(float InMP)
{
	return (MP - InMP >= 0.0f || IsBuffMode());
}

void UCStatusComponent::UpdateMP(float InMP)
{
	float temp = MP + InMP;
	MP = FMath::Clamp<float>(temp, 0, MaxMP);

	if (OnUpdateMP.IsBound())
		OnUpdateMP.Broadcast(MP);

	if(MP ==0 && IsBuffMode())
	{
		OffBuffMode();
	}

}

void UCStatusComponent::OnBuffMode()
{
	BuffMode = true;

	if (OnBuff.IsBound())
		OnBuff.Broadcast();
}

void UCStatusComponent::OffBuffMode()
{
	BuffMode = false;

	if (OffBuff.IsBound())
		OffBuff.Broadcast();
}
