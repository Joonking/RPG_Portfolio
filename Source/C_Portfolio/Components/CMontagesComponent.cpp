#include "Components/CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

//디버깅 용도로 define 추가함. 디버깅할때 주석 지워서 사용함.
//#define LOG_UCMontagesComponent 1

UCMontagesComponent::UCMontagesComponent()
{

}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataTable); //데이터 테이블이 있을때만 

	Owner = Cast<ACharacter>(GetOwner());

	TArray<FMontagesData*> datas;
	//블프에서는 행이름으로 한 행씩 불러서 배열에 추가했다면
	//C에서는 GetAllRows로 테이블에 있는 행들을 한번에 부를 수 있음.
	//한번에 부른 행들을 datas 에 넣어줌.
	 //첫 매개변수는 시작열이름, 빼도 상관없음.
	DataTable->GetAllRows<FMontagesData>("", datas);

	//테이블에 넣어준 타입별 FMontagesData를 Datas배열의 각 타입에 맞는 자리에 넣어주기.
	//타입 개수만큼. for
	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontagesData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}//for(data)
	}

#if Log_UCMontagesComponent
	for(FMontagesData* data:Datas)
	{
		if (data == nullptr)
			continue;

		FString str;
		str.Append(StaticEnum<EStateType>()->GetValueAsString(data->Type));
		str.Append(" / ");
		str.Append(data->Montage->GetPathName());
		CLog::Log(str);
	}
#endif
}

void UCMontagesComponent::PlayDeadMode()
{
	PlayAnimMontage(EStateType::Dead);

}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	CheckNull(Owner);

	//Datas에서 매개변수 타입에 맞는 FMontage 자료를 가져와서 data에 담고
	FMontagesData* data = Datas[(int32)InType];
	if (!!data && !!data->Montage) //data와 data의 Montage가 null이 아니라면
		Owner->PlayAnimMontage(data->Montage, data->PlayRatio);  //몽타주 플레이
}


