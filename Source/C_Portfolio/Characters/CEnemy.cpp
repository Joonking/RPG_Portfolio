#include "Characters/CEnemy.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CapsuleComponent.h" 
#include "Components/CAIStateComponent.h"
#include "Weapons/CWeaponStructures.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent<UCMoveComponent>(this, &Move, "Move");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Stauts");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");
	CHelpers::CreateActorComponent<UCAIStateComponent>(this, &AIState, "AIState");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//SkeletalMesh 설정
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/ThirdPerson/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);


	GetCharacterMovement()->MaxWalkSpeed = 150;
}

float ACEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Amount = damage;

	Damage.Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	//EventInstigator는 컨트롤러임. 그래서 이 컨트롤러가 소유한 Pawn을 가져와서 Character로 다운 캐스팅.

	Damage.Event = (FHitDamageEvent *)&DamageEvent;
	//DamageEvent는 래퍼런스로 받음.
	//FDamageData 구조체에 Event는 FHitDamageEvent* 포인터임. 이렇게 한 이유는
	//래퍼런스는 캐스팅이 안되니까 캐스팅을 해서 저장하려고
	//DamageEvent 만은 객체임.
	//&DamageEvent 이 객체의 주소를 받으면 포인터가 됨. 이 포인터를 우리가 원하는 자료형인
	//FHitDamageEvent로 다운 캐스팅

	State->SetHittedMode();   //State 타입 Hitted로 변경

	return damage;
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted(); break;   //새로 바뀔 타입이 Hitted 모드라면, Hitted 함수를 호출해라.
	case EStateType::Dead: Dead(); break;
	}
}

void ACEnemy::Hitted()
{
	//데미지량 Damage.Amount를 매개변수로 보내서 데미지 처리.
	Status->Damage(Damage.Amount);
	Damage.Amount = 0;   //혹시 모르니 초기화

	ChangeColor(this, HitColor);

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	//보내준 FHitData를 가져와서 처리하는 부분
	//HitData가 있을때만 해야하기에 Null 체크를 하기위해서 HitData 자료형을 포인터로 한거임
	if(!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		//Hit 몽타주 실행
		data->PlayMontage(this);

		//Launch 밀려나기, 바라보기 ------------------------------------------------------------------------
		FVector startTemp = GetActorLocation();
		FVector targetTemp = Damage.Attacker->GetActorLocation();
		FVector start = FVector(startTemp.X, startTemp.Y, 0);
		FVector target = FVector(targetTemp.X, targetTemp.Y, 0);

		FVector direction = target - start;
		direction.Normalize();

		LaunchCharacter(-direction * data->Launch, false, false);
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
		//------------------------------------------------------------------------------------------------------

		//HitStop
		data->PlayHitStop(GetWorld());

		//Sound
		data->PlaySound(this);

		//Effect
		data->PlayEffect(GetWorld(), GetActorLocation());
	}

	Damage.Attacker = nullptr;
	Damage.Event = nullptr;
}

void ACEnemy::Dead()
{
	//캡슐 Collision 꺼주기
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montages->PlayDeadMode();
}

void ACEnemy::End_Dead()
{
	Destroy();
}



