#include "Weapons/DoActions/CDoAction_Combo.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CWeaponComponent.h"
#include "Math/UnrealMathUtility.h"

void UCDoAction_Combo::DoAction(int32 InDatasIndex)
{
	Super::DoAction(InDatasIndex);

	if (bEnable)   //콤보 구간에서 공격이 들어온거라면
	{
		bEnable = false;  //우선 bEnable 꺼주고
		bExist = true;     //Exist를 켜줘서 다음 공격이 나갈 수 있도록 셋팅
		return;
	}


	//enemy라면 몇번 공격할지 정하기
	ACEnemy* enemy = Cast<ACEnemy>(Owner);
	if(!!enemy)
	{
		Index_Enemy_Max = FMath::RandRange(1, 2);
	}

	switch (DatasIndex)
	{
	case 0:
		//DoActionDatas가 없으면 리턴
		CheckFalse(DoActionDatas_1.Num() > 0);

		//콤보구간에서의 공격이 아니라면 (첫번째 공격)
		CheckFalse(State->IsIdleMode()); //Idle 모드인지 체크하고

		if(Status->IsBuffMode())  //버프 모드라면
		{
			//몽타주 개수보다 Idnex가 적을때만 실행하게끔.
			CheckFalse(Index < Buff_DoActionDatas_1.Num());
			//DoActionDatas에 Index 번째에 있는 데이터에게 DoAction 요청
			Buff_DoActionDatas_1[Index].DoAction(Owner);
		}
		else //버프 모드가 아니라면
		{
			CheckFalse(Index < DoActionDatas_1.Num());
			DoActionDatas_1[Index].DoAction(Owner);
		}
		break;
	case 1:
		CheckFalse(DoActionDatas_2.Num() > 0);
		CheckFalse(State->IsIdleMode());

		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_2.Num());
			Buff_DoActionDatas_2[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_2.Num());
			DoActionDatas_2[Index].DoAction(Owner);
		}
		break;
	case 2:
		CheckFalse(DoActionDatas_3.Num() > 0);
		CheckFalse(State->IsIdleMode());

		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_3.Num());
			Buff_DoActionDatas_3[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_3.Num());
			DoActionDatas_3[Index].DoAction(Owner);
		}
		break;
	default:
		CheckFalse(DoActionDatas_1.Num() > 0);
		CheckFalse(State->IsIdleMode());
		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_1.Num());
			Buff_DoActionDatas_1[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_1.Num());
			DoActionDatas_1[Index].DoAction(Owner);
		}
		break;
	}
}

void UCDoAction_Combo::Begin_DoAction()
{
	Super::Begin_DoAction();

	ACPlayer* player = Cast<ACPlayer>(Owner);

	if(!!player) //player 일때
	{
		CheckFalse(bExist); //bExist가 False면 바로 끝내기

		//bExist가 True면 우선 bExist 꺼주고
		bExist = false;
		++Index;
	}
	else // Enemy 일때
	{
		if(Index_Enemy_Max>=0)
		{
			Index_Enemy_Max--;
			Index++;
		}
	}

	switch (DatasIndex)
	{
	case 0:
		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_1.Num());
			Buff_DoActionDatas_1[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_1.Num());
			DoActionDatas_1[Index].DoAction(Owner);
		}

		break;
	case 1:
		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_2.Num());
			Buff_DoActionDatas_2[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_2.Num());
			DoActionDatas_2[Index].DoAction(Owner);
		}
		break;
	case 2:
		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_3.Num());
			Buff_DoActionDatas_3[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_3.Num());
			DoActionDatas_3[Index].DoAction(Owner);
		}
		break;
	default:
		if (Status->IsBuffMode())
		{
			CheckFalse(Index < Buff_DoActionDatas_1.Num());
			Buff_DoActionDatas_1[Index].DoAction(Owner);
		}
		else
		{
			CheckFalse(Index < DoActionDatas_1.Num());
			DoActionDatas_1[Index].DoAction(Owner);
		}
		break;
	}

}

void UCDoAction_Combo::End_DoAction()
{
	Super::End_DoAction();

	//인덱스 초기화
	Index = 0;

	CheckFalse(DoActionDatas_2.Num() > 0);

	if(Weapon->GetDoActionIndex()==0)
	{
		Weapon->IncreaseDoActionIndex();
		return;
	}
	if(Weapon->GetDoActionIndex() ==1)
	{
		if(DoActionDatas_3.Num()>0)
		{
			Weapon->IncreaseDoActionIndex();
			return;
		}
		Weapon->ClearDoActionIndex();
	}
	if (Weapon->GetDoActionIndex() >= 2)
		Weapon->ClearDoActionIndex();
}

void UCDoAction_Combo::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
	HittedCharacters.Empty();  //Hitted 배열에 있는 캐릭터들 모두 삭제
}


void UCDoAction_Combo::OnAttachmentBeginOverlap(ACharacter* InAttacker, UShapeComponent* InCollision,
	ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCollision, InOther);
	CheckNull(InOther);

	//HittedCharacters 배열을 for문으로 하나씩 검사하면서 HittedCharacters에 포함 되어 있는 적인지를 체크.
	for (ACharacter* hitted : HittedCharacters)
		CheckTrue(hitted == InOther); //맞은 애(InOther)가 HittedCharacters 배열에 있는 애랑 같으면 리턴해서 끝내기.

	//그렇지 않다면, HittedCharacters 배열에 맞은 애 추가.
	HittedCharacters.Add(InOther);


	// 맞은 애가 누군지를 판별 ------------------------------
	ACEnemy* enemy = Cast<ACEnemy>(InOther);
	EEnemyType enemyType;
	if(!!enemy)  //맞은 애가 적이라면
	{
		enemyType = enemy->GetEnemyType();
	}
	else   //맞은 애가 플레이어라면
	{
		enemyType = EEnemyType::Max;
	}
	//----------------------------------------------------------

	switch (enemyType)
	{
	case EEnemyType::Spartan:
		switch (DatasIndex)
		{
		case 0:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Spartan_Buff_HitDatas_1.Num());
				Spartan_Buff_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Spartan_HitDatas_1.Num());
				Spartan_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 1:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Spartan_Buff_HitDatas_2.Num());
				Spartan_Buff_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Spartan_HitDatas_2.Num());
				Spartan_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 2:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Spartan_Buff_HitDatas_3.Num());
				Spartan_Buff_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Spartan_HitDatas_3.Num());
				Spartan_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			break;
		}
		break;
	case EEnemyType::Boss:
		switch (DatasIndex)
		{
		case 0:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Boss_Buff_HitDatas_1.Num());
				Boss_Buff_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Boss_HitDatas_1.Num());
				Boss_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 1:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Boss_Buff_HitDatas_2.Num());
				Boss_Buff_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Boss_HitDatas_2.Num());
				Boss_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 2:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Boss_Buff_HitDatas_3.Num());
				Boss_Buff_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Boss_HitDatas_3.Num());
				Boss_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			break;
		}
		break;
	case EEnemyType::MBoss:
		switch (DatasIndex)
		{
		case 0:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < MBoss_Buff_HitDatas_1.Num());
				MBoss_Buff_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < MBoss_HitDatas_1.Num());
				MBoss_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 1:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < MBoss_Buff_HitDatas_2.Num());
				MBoss_Buff_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < MBoss_HitDatas_2.Num());
				MBoss_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 2:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < MBoss_Buff_HitDatas_3.Num());
				MBoss_Buff_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < MBoss_HitDatas_3.Num());
				MBoss_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			break;
		}
		break;
	case EEnemyType::Max:  //player
		switch (DatasIndex)
		{
		case 0:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Player_Buff_HitDatas_1.Num());
				Player_Buff_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Player_HitDatas_1.Num());
				Player_HitDatas_1[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 1:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Player_Buff_HitDatas_2.Num());
				Player_Buff_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Player_HitDatas_2.Num());
				Player_HitDatas_2[Index].SendDamage(InAttacker, InOther);
			}
			break;
		case 2:
			if (Status->IsBuffMode())
			{
				CheckFalse(Index < Player_Buff_HitDatas_3.Num());
				Player_Buff_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			else
			{
				CheckFalse(Index < Player_HitDatas_3.Num());
				Player_HitDatas_3[Index].SendDamage(InAttacker, InOther);
			}
			break;
		}
		break;
	}






}

