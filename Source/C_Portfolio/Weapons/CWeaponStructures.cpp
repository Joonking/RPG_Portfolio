#include "Weapons/CWeaponStructures.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Animation/AnimMontage.h"
#include "Characters/CPlayer.h"
#include "Components/CStatusComponent.h"
#include "Sound/SoundWave.h"


void FDoActionData::DoAction(ACharacter* InOwner)
{
	//State�� ActionMode�� ����
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(InOwner);
	if (!!state)
		state->SetActionMode();

	//bCanMove ó��
	UCMoveComponent* move = CHelpers::GetComponent<UCMoveComponent>(InOwner);
	if (!!move)
		bCanMove ? move ->Move() : move->Stop();

	//��Ÿ�� ����
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);


}

void FHitData::PlayMontage(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);

}

void FHitData::SendDamage(ACharacter* InAttacker, ACharacter* InOther)
{
	//�츮�� ���� FHitDamageEvent�� HitData �ڱ��ڽ��� �־ e�� �����ִ°���.
	FHitDamageEvent e;
	e.HitData = this;
	InOther->TakeDamage(Power, e, InAttacker->GetController(), nullptr);
	//ù��° �Ű����� : �� �������� ����ü�� �ִ� Power
	//�ι�° �Ű����� : FDamageEvent ����ü, FHitDamageEvent�� �츮�� ���� ����ü�� �Ѱ���.

	//������ �ְ� �÷��̾��� �÷��̾��� MP ����
	ACPlayer* player = Cast<ACPlayer>(InAttacker);
	CheckNull(player);
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(player);
	if(!status->IsBuffMode())
		status->UpdateMP(20);
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	//StopTime�� 0�̸� �������� ��������. �ٵ� StopTime�� float�ڷ�����. 
	//float�� == 0 ���� �ϸ�ȵ�. ���������� �־, �׷��� IsNearlyZero�� �����.
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<ACharacter*> characters; //������� ��� ĳ���͸� ������� ����

	//������(InWorld) ���� �����ִ� ����(GetCurrentLevel)�� �����ͼ�
	//�� �ȿ� ��� ���͵�(Actors) �� for���� ������ Character���� 
	//characters �迭�� ���.
	for(AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		ACharacter* character = Cast<ACharacter>(actor);
		if(!!character)
		{
			//�ش� ĳ������ CustomTimeDilation�� 10�� -3������ ���߱�
			character->CustomTimeDilation = 1e-3f;
			characters.Add(character);
		}
	}

	//��������Ʈ�� ���ٽ��� ����� �� ����. �Է� �޼��尡 ��ǥ���� ���ٽ���.
	//�Է¸޼���� �Լ��� �̸��� ���� �ʰ� �Լ������� �Լ��� �����ϴ� �����.
	//CreateLambda�� ���ٽ��� �����, ��ȣ �ȿ� ���ٽ��� �������ָ��.
	//�����ϰ� �Լ��� ���� �������� �ʰ� �ٷ� ���� ����� �� ����.
	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda
	(
		[=]()
		{
			//Characters���� ��� ĳ���͵��� TimeDilation 1�� �ٽ� �����ֱ�
			for (ACharacter* character : characters)
				character->CustomTimeDilation = 1.0f;
		}
	);

	FTimerHandle handle;
	InWorld->GetTimerManager().SetTimer(handle, timerDelegate, StopTime, false);
}

void FHitData::PlaySound(ACharacter* InOwner)
{
	CheckNull(Sound);
	UWorld* world = InOwner->GetWorld();
	FVector location = InOwner->GetActorLocation(); //���� ����� ��ġ

	//���� ����Լ�
	UGameplayStatics::SpawnSoundAtLocation(world, Sound, location);
}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
	CheckNull(Effect);

	FTransform transform;
	transform.SetLocation(InLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(EffectLocation);

	CHelpers::PlayEffect(InWorld, Effect, transform);

}





