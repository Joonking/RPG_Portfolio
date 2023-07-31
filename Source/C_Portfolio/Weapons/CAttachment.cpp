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

	//Collisions�� ���� ���Ͱ� ���� UShapeComponent�� ������Ʈ���� �����ͼ� �־���.
	GetComponents<UShapeComponent>(Collisions);

	//Collision�� �ϳ��ϳ��� BeginOverlap ��������Ʈ�� OnComponentBeginOverlap �Լ� ����
	for (UShapeComponent* component : Collisions)
		component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);

	OffCollision();  //BeginPlay�϶��� �켱 ��� Collision ���ֱ�

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

	//for������ Collision�� �ϳ��� ���鼭 ���ֱ�
	for (UShapeComponent* component : Collisions)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACAttachment::OffCollision()
{
	if (OffAttachmentCollision.IsBound())
		OffAttachmentCollision.Broadcast();

	//for������ Collision�� �ϳ��� ���鼭 ���ֱ�
	for (UShapeComponent* component : Collisions)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//UShapeComponent�� OnComponentBeginOverlap ��������Ʈ�� ȣ��Ǹ� �ش� �Լ��� �����.
void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//BeginOverlap �� ���Ͱ� ���� ������ �ڽ��̶�� ����
	CheckTrue(OwnerCharacter == OtherActor);

	//�ڽ��� �ƴϰ� ���� Overlap �ȰŶ��
	//OnAttachmentBeginOverlap ��������Ʈ�� ����� �Լ��� �����ֱ�
	if(OnAttachmentBeginOverlap.IsBound())
	{
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter,
			Cast<UShapeComponent>(OverlappedComponent), Cast<ACharacter>(OtherActor));
	}

}



