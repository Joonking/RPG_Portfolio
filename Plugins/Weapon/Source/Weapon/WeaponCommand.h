#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class WEAPON_API FWeaponCommand
	: public TCommands<FWeaponCommand>
{
public:
	FWeaponCommand();
	~FWeaponCommand();

	void RegisterCommands() override;

public:
	void Startup();

private:
	//���� �߰��ɶ� ����� �Լ��� ����� ����� ��⿡�� �����Ұ���.
	//���� Example �Ҷ��� ExampleModule�� ���������.
	//�̹����� Command ������ ���°���. 
	void ToolBar_Added(FToolBarBuilder& InBuilder);  //���ٰ� �߰��ɶ� ȣ��� �Լ� 
	void ToolBar_Button_Clicked();  //��ư �������� ȣ���� �Լ�


public:
	TSharedPtr<FExtender> Extender;  //���ٿ��� ����� Extender

	TSharedPtr<FUICommandInfo> Id;
	TSharedPtr<FUICommandList> Command;

};