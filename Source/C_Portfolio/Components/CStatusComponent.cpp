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
	//����� ���������� �Ű������� �־��ְ�, 
	//���ο��� ���� -���� ���̷��� -1�� ������.

	HP = FMath::Clamp(HP, 0.0f, MaxHP);

	//������ �޾����� ȣ������ ��������Ʈ
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
