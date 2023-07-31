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
	


	//ĳ���� ��ġ, ���� ����
	GetMesh()->SetRelativeLocation(FVector(0, 0, -91));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//SkeletalMesh ����
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/GirlSparta/Mesh/SK_GS_Clothe.SK_GS_Clothe'");
	GetMesh()->SetSkeletalMesh(mesh);

	//�ִϸ��̼� ���� ����
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	GetMesh()->SetAnimClass(animInstance);

	//SpringArm�� ��ġ ����
	SpringArm->SetRelativeLocation(FVector(0, 0, 115));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 220;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	Camera->SetRelativeLocation(FVector(0, 0, 10));

	//bOrientRotation�� ������ �ӵ�
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	Around->SetSphereRadius(1500);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Amount = damage;

	Damage.Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	//EventInstigator�� ��Ʈ�ѷ���. �׷��� �� ��Ʈ�ѷ��� ������ Pawn�� �����ͼ� Character�� �ٿ� ĳ����.

	Damage.Event = (FHitDamageEvent *)&DamageEvent;
	//DamageEvent�� ���۷����� ����.
	//FDamageData ����ü�� Event�� FHitDamageEvent* ��������. �̷��� �� ������
	//���۷����� ĳ������ �ȵǴϱ� ĳ������ �ؼ� �����Ϸ���
	//DamageEvent ���� ��ü��.
	//&DamageEvent �� ��ü�� �ּҸ� ������ �����Ͱ� ��. �� �����͸� �츮�� ���ϴ� �ڷ�����
	//FHitDamageEvent�� �ٿ� ĳ����

	State->SetHittedMode();   //State Ÿ�� Hitted�� ����

	return damage;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//��������Ʈ ����
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

	//����� �̺�Ʈ ���� ====================================================================
	PlayerInputComponent->BindAxis("MoveForward", Move, &UCMoveComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", Move, &UCMoveComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", Move, &UCMoveComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", Move, &UCMoveComponent::OnVerticlaLook);
	//=================================================================================

	//�Է� ���� �̺�Ʈ ���� ==================================================================
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
	case EStateType::Hitted: Hitted(); break;   //���� �ٲ� Ÿ���� Hitted �����, Hitted �Լ��� ȣ���ض�.
	case EStateType::Dead: Dead(); break;
	}
}

void ACPlayer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//BeginOverlap �� ���Ͱ� �ڽ��̶�� ����
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
	//�������� Damage.Amount�� �Ű������� ������ ������ ó��.
	Status->Damage(Damage.Amount);
	Damage.Amount = 0;   //Ȥ�� �𸣴� �ʱ�ȭ

	ChangeColor(this, HitColor);

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	//������ FHitData�� �����ͼ� ó���ϴ� �κ�
	//HitData�� �������� �ؾ��ϱ⿡ Null üũ�� �ϱ����ؼ� HitData �ڷ����� �����ͷ� �Ѱ���
	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		//Hit ��Ÿ�� ����
		data->PlayMontage(this);

		//Launch �з�����, �ٶ󺸱� ------------------------------------------------------------------------
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

//ToDo : �÷��̾� ����
void ACPlayer::Dead()
{
	//ĸ�� Collision ���ֱ�
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
