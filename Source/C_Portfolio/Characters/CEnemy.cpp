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

	//SkeletalMesh ����
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

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted(); break;   //���� �ٲ� Ÿ���� Hitted �����, Hitted �Լ��� ȣ���ض�.
	case EStateType::Dead: Dead(); break;
	}
}

void ACEnemy::Hitted()
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
	if(!!Damage.Event && !!Damage.Event->HitData)
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

void ACEnemy::Dead()
{
	//ĸ�� Collision ���ֱ�
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montages->PlayDeadMode();
}

void ACEnemy::End_Dead()
{
	Destroy();
}



