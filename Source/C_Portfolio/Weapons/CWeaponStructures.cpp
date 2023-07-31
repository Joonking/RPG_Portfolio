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
	//State를 ActionMode로 변경
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(InOwner);
	if (!!state)
		state->SetActionMode();

	//bCanMove 처리
	UCMoveComponent* move = CHelpers::GetComponent<UCMoveComponent>(InOwner);
	if (!!move)
		bCanMove ? move ->Move() : move->Stop();

	//몽타주 실행
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
	//우리가 만든 FHitDamageEvent에 HitData 자기자신을 넣어서 e를 보내주는거임.
	FHitDamageEvent e;
	e.HitData = this;
	InOther->TakeDamage(Power, e, InAttacker->GetController(), nullptr);
	//첫번째 매개변수 : 줄 데미지량 구조체에 있는 Power
	//두번째 매개변수 : FDamageEvent 구조체, FHitDamageEvent로 우리가 만든 구조체를 넘겨줌.

	//때리는 애가 플레이어라면 플레이어의 MP 증가
	ACPlayer* player = Cast<ACPlayer>(InAttacker);
	CheckNull(player);
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(player);
	if(!status->IsBuffMode())
		status->UpdateMP(20);
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	//StopTime이 0이면 수행하지 않을거임. 근데 StopTime은 float자료형임. 
	//float는 == 0 으로 하면안됨. 오차범위가 있어서, 그래서 IsNearlyZero를 사용함.
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<ACharacter*> characters; //월드상의 모든 캐릭터를 담기위한 변수

	//월드의(InWorld) 현재 열려있는 레벨(GetCurrentLevel)을 가져와서
	//그 안에 모든 액터들(Actors) 을 for문을 돌려서 Character들을 
	//characters 배열에 담기.
	for(AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		ACharacter* character = Cast<ACharacter>(actor);
		if(!!character)
		{
			//해당 캐릭터의 CustomTimeDilation을 10에 -3승으로 낮추기
			character->CustomTimeDilation = 1e-3f;
			characters.Add(character);
		}
	}

	//델리게이트는 람다식을 사용할 수 있음. 입력 메서드가 대표적인 람다식임.
	//입력메서드는 함수의 이름을 쓰지 않고 함수내에서 함수를 정의하는 방식임.
	//CreateLambda로 람다식을 만들고, 괄호 안에 람다식을 정의해주면됨.
	//간편하게 함수를 따로 정의하지 않고 바로 만들어서 사용할 수 있음.
	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda
	(
		[=]()
		{
			//Characters들의 모든 캐릭터들의 TimeDilation 1로 다시 돌려주기
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
	FVector location = InOwner->GetActorLocation(); //사운드 재생할 위치

	//사운드 재생함수
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





