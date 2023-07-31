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
	//툴바 추가될때 사용할 함수를 여기다 만들어 모듈에서 연결할거임.
	//전에 Example 할때는 ExampleModule에 만들었었음.
	//이번에는 Command 쪽으로 빼는거임. 
	void ToolBar_Added(FToolBarBuilder& InBuilder);  //툴바가 추가될때 호출될 함수 
	void ToolBar_Button_Clicked();  //버튼 눌렀을때 호출할 함수


public:
	TSharedPtr<FExtender> Extender;  //툴바에서 사용할 Extender

	TSharedPtr<FUICommandInfo> Id;
	TSharedPtr<FUICommandList> Command;

};