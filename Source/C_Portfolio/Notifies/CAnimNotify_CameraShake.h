#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_CameraShake.generated.h"


UCLASS()
class C_PORTFOLIO_API UCAnimNotify_CameraShake : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera") //EditAnywhere로 에디터 상에서 변수에 클래스를 지정해줄 수 있도록만들기
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;   //TSubclassOf를 이용해서 UMatineeCameraShake 이하 클래스들만 선택할 수 있게 클래스 변수 생성
public:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};




