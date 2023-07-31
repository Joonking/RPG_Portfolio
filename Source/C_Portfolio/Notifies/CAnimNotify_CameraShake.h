#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_CameraShake.generated.h"


UCLASS()
class C_PORTFOLIO_API UCAnimNotify_CameraShake : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera") //EditAnywhere�� ������ �󿡼� ������ Ŭ������ �������� �� �ֵ��ϸ����
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;   //TSubclassOf�� �̿��ؼ� UMatineeCameraShake ���� Ŭ�����鸸 ������ �� �ְ� Ŭ���� ���� ����
public:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};




