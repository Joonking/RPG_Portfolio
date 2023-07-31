#include "Components/CMoveComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCMoveComponent::UCMoveComponent()
{

}

void UCMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	//SetSpeed(ESpeedType::Sprint);
	DisableControlRotation();
}

//�� �ڷ� �̵� �Լ�
void UCMoveComponent::OnMoveForward(float InAxis)
{
	CheckFalse(bCanMove);

	//Owner�� GetControlRotation.Yaw()�� �����´��� GetForwardVector�� ������ ������.
	//�״��� �� �������� ĳ���͸� �������ٰ���.
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	//rotator���� ������� ���ϴ� �Լ��� ��� Quat���� ������
	FVector direction = FQuat(rotator).GetForwardVector();

	//AddMovementInput�� ���������� DeltaTime�� ������.
	Owner->AddMovementInput(direction, InAxis);
}

//�¿�� �̵� �Լ�
void UCMoveComponent::OnMoveRight(float InAxis)
{
	CheckFalse(bCanMove);

	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	Owner->AddMovementInput(direction, InAxis);
}

//���콺 �� �� �̵� �Լ�
void UCMoveComponent::OnHorizontalLook(float InAxis)
{
	//AddControllerYawInput�� ���������� DeltaTime�� ���ϴ°� ����.
	//�׷��� GetWorld�� GetDeltaSeconds�� �����ͼ� ���������. �̶� MouseSpeed�� ���ؼ� ������ ��������.
	Owner->AddControllerYawInput(InAxis * MouseSpeed.X * GetWorld()->GetDeltaSeconds());
}

//���콺 �� �� �̵� �Լ�
void UCMoveComponent::OnVerticlaLook(float InAxis)
{
	Owner->AddControllerPitchInput(InAxis*MouseSpeed.Y * GetWorld()->GetDeltaSeconds());
}

//���ǵ� ���� �Լ�
void UCMoveComponent::SetSpeed(ESpeedType InType)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

//ī�޶� ����
void UCMoveComponent::EnableControlRotation()
{
	Owner->bUseControllerRotationYaw = true;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
}

//����ȹ�
void UCMoveComponent::DisableControlRotation()
{
	Owner->bUseControllerRotationYaw = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
}


