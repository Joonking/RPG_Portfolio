#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "SWeaponListView.h"

class WEAPON_API FWeaponAssetEditor
	: public FAssetEditorToolkit
{

public:
	//�� �Լ��� â�� �������� �������.
	//������ ����Ŭ���ؼ� ���� InAssetName���� ���� �̸��� ��ܼ� ȣ��ǰ� �Ұ���. 
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown(); //â�� ������ ȣ���� �Լ�

private:
	void Open(FString InAssetName);

protected:
	bool OnRequestClose() override;

public:
	//�θ� FAssetEditorToolkit�� �ִ� �� ������ �ؾ��� �����Լ��� -----------------
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	FName GetToolkitFName() const override;				//ToolKit �̸� ����
	FText GetBaseToolkitName() const override;           //BaseToolKit �̸�����
	FString GetWorldCentricTabPrefix() const override;   //������ �ϴܿ� �ߴ� â �̸�����
	virtual FLinearColor GetWorldCentricTabColorScale() const override; //â�� ����
	//-------------------------------------------------------------------------

private:
	//SDockTab : S�� �����ֵ��� ������Ʈ��. Docking ������ �� ��ü��. Docking(��ŷ)�� ���� ���� �ٸ� �ܿ� ���̴°� �ǹ���. 
	//FOnSpawnTab ��������Ʈ�� ��������� �Լ�. �� �Լ� �ȿ��� �� �ǵ鿡 �������� ������Ʈ���� �����Ұ���. 
	TSharedRef<SDockTab> Spawn_ListViewTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsTab(const FSpawnTabArgs& InArgs);

private:
	void WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr);

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;

private:
	static const FName EditorName;
	static const FName ListViewTabId;  //���� ���� �̸����� ����� FName �߰�
	static const FName DetailsTabId;   //������ ���� �̸�.

private:
	TSharedPtr<class SWeaponListView> ListView;
	TSharedPtr<class IDetailsView> DetailsView;

};