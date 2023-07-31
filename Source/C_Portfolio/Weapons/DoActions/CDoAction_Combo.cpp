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

	if (bEnable)   //�޺� �������� ������ ���°Ŷ��
	{
		bEnable = false;  //�켱 bEnable ���ְ�
		bExist = true;     //Exist�� ���༭ ���� ������ ���� �� �ֵ��� ����
		return;
	}


	//enemy��� ��� �������� ���ϱ�
	ACEnemy* enemy = Cast<ACEnemy>(Owner);
	if(!!enemy)
	{
		Index_Enemy_Max = FMath::RandRange(1, 2);
	}

	switch (DatasIndex)
	{
	case 0:
		//DoActionDatas�� ������ ����
		CheckFalse(DoActionDatas_1.Num() > 0);

		//�޺����������� ������ �ƴ϶�� (ù��° ����)
		CheckFalse(State->IsIdleMode()); //Idle ������� üũ�ϰ�

		if(Status->IsBuffMode())  //���� �����
		{
			//��Ÿ�� �������� Idnex�� �������� �����ϰԲ�.
			CheckFalse(Index < Buff_DoActionDatas_1.Num());
			//DoActionDatas�� Index ��°�� �ִ� �����Ϳ��� DoAction ��û
			Buff_DoActionDatas_1[Index].DoAction(Owner);
		}
		else //���� ��尡 �ƴ϶��
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

	if(!!player) //player �϶�
	{
		CheckFalse(bExist); //bExist�� False�� �ٷ� ������

		//bExist�� True�� �켱 bExist ���ְ�
		bExist = false;
		++Index;
	}
	else // Enemy �϶�
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

	//�ε��� �ʱ�ȭ
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
	HittedCharacters.Empty();  //Hitted �迭�� �ִ� ĳ���͵� ��� ����
}


void UCDoAction_Combo::OnAttachmentBeginOverlap(ACharacter* InAttacker, UShapeComponent* InCollision,
	ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCollision, InOther);
	CheckNull(InOther);

	//HittedCharacters �迭�� for������ �ϳ��� �˻��ϸ鼭 HittedCharacters�� ���� �Ǿ� �ִ� �������� üũ.
	for (ACharacter* hitted : HittedCharacters)
		CheckTrue(hitted == InOther); //���� ��(InOther)�� HittedCharacters �迭�� �ִ� �ֶ� ������ �����ؼ� ������.

	//�׷��� �ʴٸ�, HittedCharacters �迭�� ���� �� �߰�.
	HittedCharacters.Add(InOther);


	// ���� �ְ� �������� �Ǻ� ------------------------------
	ACEnemy* enemy = Cast<ACEnemy>(InOther);
	EEnemyType enemyType;
	if(!!enemy)  //���� �ְ� ���̶��
	{
		enemyType = enemy->GetEnemyType();
	}
	else   //���� �ְ� �÷��̾���
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

