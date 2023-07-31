#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "SWeaponListView.h"

class WEAPON_API FWeaponAssetEditor
	: public FAssetEditorToolkit
{

public:
	//이 함수로 창이 열리도록 만들거임.
	//에셋을 더블클릭해서 열면 InAssetName으로 에셋 이름이 담겨서 호출되게 할거임. 
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown(); //창이 닫힐때 호출할 함수

private:
	void Open(FString InAssetName);

protected:
	bool OnRequestClose() override;

public:
	//부모 FAssetEditorToolkit에 있는 꼭 재정의 해야할 가상함수들 -----------------
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	FName GetToolkitFName() const override;				//ToolKit 이름 정의
	FText GetBaseToolkitName() const override;           //BaseToolKit 이름정의
	FString GetWorldCentricTabPrefix() const override;   //윈도우 하단에 뜨는 창 이름정의
	virtual FLinearColor GetWorldCentricTabColorScale() const override; //창의 색상
	//-------------------------------------------------------------------------

private:
	//SDockTab : S가 붙은애들은 슬레이트임. Docking 가능한 탭 객체임. Docking(도킹)은 탭을 떼서 다른 텝에 붙이는걸 의미함. 
	//FOnSpawnTab 델리게이트에 연결시켜줄 함수. 이 함수 안에서 각 탭들에 세부적인 슬레이트들을 정의할거임. 
	TSharedRef<SDockTab> Spawn_ListViewTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsTab(const FSpawnTabArgs& InArgs);

private:
	void WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr);

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;

private:
	static const FName EditorName;
	static const FName ListViewTabId;  //왼쪽 영역 이름으로 사용할 FName 추가
	static const FName DetailsTabId;   //오른쪽 영역 이름.

private:
	TSharedPtr<class SWeaponListView> ListView;
	TSharedPtr<class IDetailsView> DetailsView;

};