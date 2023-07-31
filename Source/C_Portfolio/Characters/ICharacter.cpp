#include "Characters/ICharacter.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"


void IICharacter::ChangeColor(ACharacter* InCharacter, FLinearColor InColor)
{
	InCharacter->GetMesh()->SetVectorParameterValueOnMaterials("EffectColor", UKismetMathLibrary::Conv_LinearColorToVector(InColor));
	InCharacter->GetMesh()->SetScalarParameterValueOnMaterials("StartTime", InCharacter->GetWorld()->GetTimeSeconds());
}
