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

//앞 뒤로 이동 함수
void UCMoveComponent::OnMoveForward(float InAxis)
{
	CheckFalse(bCanMove);

	//Owner의 GetControlRotation.Yaw()를 가져온다음 GetForwardVector로 전방을 가져옴.
	//그다음 그 방향으로 캐릭터를 움직여줄거임.
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	//rotator에는 전방방향 구하는 함수가 없어서 Quat으로 변경함
	FVector direction = FQuat(rotator).GetForwardVector();

	//AddMovementInput은 내부적으로 DeltaTime을 곱해줌.
	Owner->AddMovementInput(direction, InAxis);
}

//좌우로 이동 함수
void UCMoveComponent::OnMoveRight(float InAxis)
{
	CheckFalse(bCanMove);

	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	Owner->AddMovementInput(direction, InAxis);
}

//마우스 좌 우 이동 함수
void UCMoveComponent::OnHorizontalLook(float InAxis)
{
	//AddControllerYawInput은 내부적으로 DeltaTime을 곱하는게 없음.
	//그래서 GetWorld에 GetDeltaSeconds를 가져와서 곱해줘야함. 이때 MouseSpeed를 곱해서 감도를 설정해줌.
	Owner->AddControllerYawInput(InAxis * MouseSpeed.X * GetWorld()->GetDeltaSeconds());
}

//마우스 상 하 이동 함수
void UCMoveComponent::OnVerticlaLook(float InAxis)
{
	Owner->AddControllerPitchInput(InAxis*MouseSpeed.Y * GetWorld()->GetDeltaSeconds());
}

//스피드 설정 함수
void UCMoveComponent::SetSpeed(ESpeedType InType)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

//카메라 고정
void UCMoveComponent::EnableControlRotation()
{
	Owner->bUseControllerRotationYaw = true;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
}

//사방팔방
void UCMoveComponent::DisableControlRotation()
{
	Owner->bUseControllerRotationYaw = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
}


