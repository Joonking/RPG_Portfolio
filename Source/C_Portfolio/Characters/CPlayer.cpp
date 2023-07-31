#include "Characters/CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMoveComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/CWeaponStructures.h"

ACPlayer::ACPlayer()
{
 	PrimaryActorTick.bCanEverTick = true;

	//SpringArm
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	//Camera
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	//Around
	CHelpers::CreateComponent<USphereComponent>(this, &Around, "Around", GetMesh());

	//MoveComponent
	CHelpers::CreateActorComponent<UCMoveComponent>(this, &Move, "Move");
	//StatusComponent
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	//StateComponent
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	//MontageComponent
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	//WeaponComponent
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");
	


	//캐릭터 위치, 방향 조정
	GetMesh()->SetRelativeLocation(FVector(0, 0, -91));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//SkeletalMesh 설정
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/GirlSparta/Mesh/SK_GS_Clothe.SK_GS_Clothe'");
	GetMesh()->SetSkeletalMesh(mesh);

	//애니메이션 블프 설정
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	GetMesh()->SetAnimClass(animInstance);

	//SpringArm의 위치 설정
	SpringArm->SetRelativeLocation(FVector(0, 0, 115));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 220;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	Camera->SetRelativeLocation(FVector(0, 0, 10));

	//bOrientRotation의 돌릴때 속도
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	Around->SetSphereRadius(1500);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
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

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//델리게이트 연결
	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	Around->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnComponentBeginOverlap);
	Around->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::OnComponentEndOverlap);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetAroundEnemy();

	if (Status->IsBuffMode())
		Status->UpdateMP(-0.028);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//축매핑 이벤트 연결 ====================================================================
	PlayerInputComponent->BindAxis("MoveForward", Move, &UCMoveComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", Move, &UCMoveComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", Move, &UCMoveComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", Move, &UCMoveComponent::OnVerticlaLook);
	//=================================================================================

	//입력 매핑 이벤트 연결 ==================================================================
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::DoAction);

	PlayerInputComponent->BindAction("Skill_1", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Skill_1_Pressed);
	PlayerInputComponent->BindAction("Skill_1", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::SKill_1_Released);

	PlayerInputComponent->BindAction("Skill_2", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Skill_2_Pressed);
	PlayerInputComponent->BindAction("Skill_2", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::SKill_2_Released);

	PlayerInputComponent->BindAction("Skill_3", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Skill_3_Pressed);
	PlayerInputComponent->BindAction("Skill_3", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::SKill_3_Released);

	PlayerInputComponent->BindAction("Skill_4", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Skill_4_Pressed);
	PlayerInputComponent->BindAction("Skill_4", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::SKill_4_Released);

	//=================================================================================

}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted(); break;   //새로 바뀔 타입이 Hitted 모드라면, Hitted 함수를 호출해라.
	case EStateType::Dead: Dead(); break;
	}
}

void ACPlayer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//BeginOverlap 된 액터가 자신이라면 리턴
	CheckTrue(this == OtherActor);

	//CLog::Print(OtherActor);
	AroundEnemies.AddUnique(Cast<ACharacter>(OtherActor));
}

void ACPlayer::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(this == OtherActor);

	//CLog::Print(OtherActor);

	for(ACharacter* Enemy : AroundEnemies)
	{
		if(Enemy == Cast<ACharacter>(OtherActor))
		{
			AroundEnemies.RemoveSingle(Enemy);
			return;
		}
	}

}


void ACPlayer::Hitted()
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
	if (!!Damage.Event && !!Damage.Event->HitData)
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

//ToDo : 플레이어 데드
void ACPlayer::Dead()
{
	//캡슐 Collision 꺼주기
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACPlayer::End_Dead()
{
	Destroy();
}

void ACPlayer::SetAroundEnemy()
{
	if(AroundEnemies.Num() != 0)
	{
		if(!!AroundEnemy)
		{
			for(ACharacter* Enemy : AroundEnemies)
			{
				if(this->GetDistanceTo(AroundEnemy) > this->GetDistanceTo(Enemy))
				{
					AroundEnemy = Enemy;
				}
			}
		}
		else
		{
			AroundEnemy = AroundEnemies[0];
		}
	}
	else
	{
		if(!!AroundEnemy)
		{
			AroundEnemy = nullptr;
		}
	}
}

void ACPlayer::TargetAction()
{
	CheckNull(AroundEnemy);

	FVector start = FVector(this->GetActorLocation().X, this->GetActorLocation().Y,0);
	FVector end = FVector(AroundEnemy->GetActorLocation().X, AroundEnemy->GetActorLocation().Y, 0);
	this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, end));

}
