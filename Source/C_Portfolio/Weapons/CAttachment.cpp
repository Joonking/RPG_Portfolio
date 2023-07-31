#include "Weapons/CAttachment.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//Collisions에 무기 액터가 가진 UShapeComponent형 컴포넌트들을 가져와서 넣어줌.
	GetComponents<UShapeComponent>(Collisions);

	//Collision들 하나하나의 BeginOverlap 델리게이트에 OnComponentBeginOverlap 함수 연결
	for (UShapeComponent* component : Collisions)
		component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);

	OffCollision();  //BeginPlay일때는 우선 모든 Collision 꺼주기

	Super::BeginPlay();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToCollision(UShapeComponent* InCollision, FName InSocketName)
{
	InCollision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnCollision()
{
	if (OnAttachmentCollision.IsBound())
		OnAttachmentCollision.Broadcast();

	//for문으로 Collision들 하나씩 돌면서 켜주기
	for (UShapeComponent* component : Collisions)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACAttachment::OffCollision()
{
	if (OffAttachmentCollision.IsBound())
		OffAttachmentCollision.Broadcast();

	//for문으로 Collision들 하나씩 돌면서 꺼주기
	for (UShapeComponent* component : Collisions)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//UShapeComponent의 OnComponentBeginOverlap 델리게이트가 호출되면 해당 함수가 실행됨.
void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//BeginOverlap 된 액터가 무기 소유자 자신이라면 리턴
	CheckTrue(OwnerCharacter == OtherActor);

	//자신이 아니고 적이 Overlap 된거라면
	//OnAttachmentBeginOverlap 델리게이트에 연결된 함수들 콜해주기
	if(OnAttachmentBeginOverlap.IsBound())
	{
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter,
			Cast<UShapeComponent>(OverlappedComponent), Cast<ACharacter>(OtherActor));
	}

}



