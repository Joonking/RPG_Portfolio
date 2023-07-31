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
	CheckNull(CameraShakeClass);   //CameraShakeClass ������ �����Ǿ����� ������ ����

	ACharacter* character = MeshComp->GetOwner<ACharacter>();
	CheckNull(character);
	
	//ĳ������ ��Ʈ�ѷ��� PlayerController���·� ������ controller�� ���
	//APlayerController* controller = character->GetController<APlayerController>();

	APlayerController* controller = character->GetWorld()->GetFirstPlayerController();
	CheckNull(controller);  //PlayerController�� ������ ����

	controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);  //CameraShakeClass������ ī�޶� ����ũ
}