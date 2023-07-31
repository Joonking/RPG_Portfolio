#include "WeaponCommand.h"
#include "WeaponStyle.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"
#include "WeaponAssetEditor.h" 

FWeaponCommand::FWeaponCommand()
	: TCommands("Weapon", FText::FromString("Weapon Asset Editor"),
		NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

//모듈 시작할 때, 콜해줄 함수
void FWeaponCommand::Startup()
{
	FWeaponCommand::RegisterCommands();

	Extender = MakeShareable(new FExtender());

	//툴바 등록해주는 부분. 
	FToolBarExtensionDelegate toolbar = FToolBarExtensionDelegate::CreateRaw(this,
		&FWeaponCommand::ToolBar_Added);
	Extender->AddToolBarExtension("Settings", EExtensionHook::After, Command, toolbar);
	//Settings 버튼 뒤에다가 버튼 추가.

	//Extender를 레벨 에디터에 등록 시켜주는 부분 
	FLevelEditorModule& levelEditor =
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);

}


FWeaponCommand::~FWeaponCommand()
{
	if (Command.IsValid())
		Command.Reset();

	if (Extender.IsValid())
		Extender.Reset();
}

void FWeaponCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(Id, "Weapon", "Weapon Asset Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	Command->MapAction(Id, FExecuteAction::CreateRaw(this, &FWeaponCommand::ToolBar_Button_Clicked),
		FCanExecuteAction());
}

//툴바가 추가될때 호출될 함수
void FWeaponCommand::ToolBar_Added(FToolBarBuilder& InBuilder)
{
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton(Id, NAME_None, FText::FromString("Weapon"),
		FText::FromString("Weapon Asset Editor"), FWeaponStyle::Get()->ToolBar_Icon, NAME_None);

}

//버튼 클릭했을때 호출될 함수
//실질적인 Command 부분.
void FWeaponCommand::ToolBar_Button_Clicked()
{
	FWeaponAssetEditor::OpenWindow();   //버튼을 클릭했을때 WeaponAssetEditor의 OpenWindow 함수를 콜해서 창을 열 수 있도록. 

}