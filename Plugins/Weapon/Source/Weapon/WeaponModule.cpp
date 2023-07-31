#include "WeaponModule.h"
#include "WeaponStyle.h"
#include "WeaponCommand.h"
#include "AssetTypeActions_Weapon.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FWeaponModule"

void FWeaponModule::StartupModule()
{
	FWeaponStyle::Get();

	Command = MakeShareable(new FWeaponCommand());
	Command->Startup();


	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type type = assetTools.RegisterAdvancedAssetCategory("Weapon", FText::FromName("Weapon"));  //컨텐츠 브라우저 우클릭해서 출력될 카테고리 이름 Weapon

	AssetTypeAction = MakeShareable(new FAssetTypeActions_Weapon(type));
	assetTools.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
}

void FWeaponModule::ShutdownModule()
{
	if (Command.IsValid())
		Command.Reset();

	if (AssetTypeAction.IsValid())
		AssetTypeAction.Reset();

	FWeaponStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWeaponModule, Weapon)