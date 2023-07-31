#include "Notifies/CAnimNotify_CameraShake.h"
#include "Global.h"
#include "Camera/CameraShake.h"   
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FString UCAnimNotify_CameraShake::GetNotifyName_Implementation() const
{
	return "CameraShake";
}

void UCAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	CheckNull(CameraShakeClass);   //CameraShakeClass 변수가 설정되어있지 않으면 리턴

	ACharacter* character = MeshComp->GetOwner<ACharacter>();
	CheckNull(character);
	
	//캐릭터의 컨트롤러를 PlayerController형태로 가져와 controller에 담고
	//APlayerController* controller = character->GetController<APlayerController>();

	APlayerController* controller = character->GetWorld()->GetFirstPlayerController();
	CheckNull(controller);  //PlayerController가 없으면 리턴

	controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);  //CameraShakeClass변수로 카메라 쉐이크
}