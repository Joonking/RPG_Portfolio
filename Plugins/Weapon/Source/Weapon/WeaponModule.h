#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FWeaponModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FWeaponCommand> Command;
	TSharedPtr<class IAssetTypeActions> AssetTypeAction;
};