#include "WeaponAssetEditor.h"
#include "Widgets/Docking/SDockTab.h"

#include "WeaponDetailsView.h"
#include "WeaponEquipmentData.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "ListView";  //���� â �̸�.
const FName FWeaponAssetEditor::DetailsTabId = "Details";  //������ â �̸�

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	//�̹� â�� ������ â �ݰ� �������ش����� ���� ���°���. 
	if (Instance.IsValid())
	{
		if(Instance->ListView.IsValid())
		{
			//â ����, ����Ʈ �� ������ ����
			FWeaponRowDataPtr ptr = nullptr;

			if (InAssetName.Len() > 0)
				ptr = Instance->ListView->GetRowDataPtrByName(InAssetName);

			if (ptr == nullptr)
				ptr = Instance->ListView->GetFirstDataPtr();

			Instance->ListView->SelectDataPtr(ptr->Asset);
			return;
		}
		else
		{
			//������ ������ ���� ��Ȳ
			Instance->CloseWindow();
			Instance.Reset();
			Instance = nullptr;

		}
	}

	//Instance�� �̱����̶� �ϳ��� �����ϰ� OpenWindow �Լ��� �� �ɶ� ������.
	Instance = MakeShareable(new FWeaponAssetEditor());
	//���ο��� ����ϴ� Open �Լ��� ȣ���ؼ� â�� �����.
	Instance->Open(InAssetName);
}

//â�� �������� ����������ϴ� �͵��� ���� �Լ�
void FWeaponAssetEditor::Open(FString InAssetName)
{
	//���� �� ListView ���� -----------------------------------------------------------------------------------------------
	ListView = SNew(SWeaponListView)
		.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::WeaponListViewSelectedItem);
	//-------------------------------------------------------------------------------------------------------------------------

	//������ �� DetailsView ���� ---------------------------------------------------------------------------------------------------------

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//������ â�� ������ ���� "EquipmentData" Ÿ���� FWeaponEquipmentData �ν��Ͻ��� ���� �������. �ڿ��� �������̼� �Ű�������. 
	prop.RegisterCustomPropertyTypeLayout("EquipmentData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(FWeaponEquipmentData::MakeInstance));
	prop.NotifyCustomizationModuleChanged();

	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	args.ViewIdentifier = "WeaponAssetEditorDetailsView";

	DetailsView = prop.CreateDetailView(args);

	FOnGetDetailCustomizationInstance detailsView = FOnGetDetailCustomizationInstance::CreateStatic(&FWeaponDetailsView::MakeInstance);

	DetailsView->SetGenericLayoutDetailsDelegate(detailsView);

	//------------------------------------------------------------------------------------------------------------------------------------------


	TSharedRef<FTabManager::FLayout> layout =
		FTabManager::NewLayout("WeaponAssetEditor_Layout")
		->AddArea
		(
			//NewPrimaryArea �� �� ������. �� ������ �����ϴ°���. 
			//SetOrientation(Orient_Vertical) : �������� ������.
			//| ������ �ƴ� �� ������. �� �̷��� ������ ���ʿ� ���ٸ� ��ġ �ϰ� 
			//�Ʒ����� �� �ο������� ��������.
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split   //������ �����°���. ���Ⱑ ���ٿ��� ==================
			(
				FTabManager::NewStack()  //���⼭ ���ο� ������ �����ϰڴٴ°���. 
				//Stack�� ����������.
				->SetSizeCoefficient(0.1f)  //������ ũ�� 10���� ���� ����ϰڴ�. 
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			) //===============================================
			->Split  //���� �� ���� ���� ================================================
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split //���� ���� --------------------------------------
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f)
					->AddTab(ListViewTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				) //-----------------------------------------------------
				->Split //������ ���� ------------------------------------
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f)
					->AddTab(DetailsTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				) //-----------------------------------------------------
			)//========================================================================

		);

	//WeaponAssetEditor â�� ���� �ΰ��� ��� 
	//1�� : ������ �������� �ִ� WeaponAsset�� ���� ��� ( ���� ��� DA_Fist �� ���� Ŭ���ؼ� ���� ���)
	//2�� : ��� WeaponAsset�� �������� �ʰ� ���� ���ٿ� �ִ� Weapon ��ư�� ������ â�� ���°��.

	UCWeaponAsset* asset = nullptr;
	if (InAssetName.Len() > 0)
	{
		FWeaponRowDataPtr ptr = ListView->GetRowDataPtrByName(InAssetName);

		if (ListView->SelectedRowDataPtrName() == InAssetName)
			return;

		if (ptr.IsValid() == false)
			asset = ListView->GetFirstDataPtr()->Asset;
		else
			asset = ptr->Asset;
	}
	else
	{
		asset = ListView->GetFirstDataPtr()->Asset;
	}

	InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, layout, true, true, asset);

	//DetailsView->SetObject(asset);
	ListView->SelectDataPtr(asset);

}

//â�� ������
bool FWeaponAssetEditor::OnRequestClose()
{
	FWeaponEquipmentData::RemoveCheckBoxes();

	if(DetailsView.IsValid())
	{
		if (!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);
	}

	//PropertyEditor ����� �ҷ��������� �ϴ� Ȯ���ϰ�
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.UnregisterCustomPropertyTypeLayout("EquipmentData");
		prop.NotifyCustomizationModuleChanged();
	}

	if (ListView.IsValid())
		ListView.Reset();

	if (DetailsView.IsValid())
		DetailsView.Reset();

	return true;
}


void FWeaponAssetEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

//���� Spawn ��Ű�� �ָ� ��Ͻ�Ű�ڴ� ��� �Լ���. �θ��Լ� �������Ѱ�
//���� ���� �ϴ� �κ�. Id�� �����ؼ� �ǵ��� ������.
void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_ListViewTab);
	InTabManager->RegisterTabSpawner(ListViewTabId, tab);

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_DetailsTab);
	InTabManager->RegisterTabSpawner(DetailsTabId, tab2);
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		.Content()
		[
			ListView.ToSharedRef()
		];
}

//������ ������ â�� ������ ������ �߰����ָ��. 
TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_DetailsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		.Content()
		[
			DetailsView.ToSharedRef()
		];
}

FName FWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

void FWeaponAssetEditor::WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr)
{
	if (InPtr == nullptr)
		return;

	if (!!GetEditingObject())
		RemoveEditingObject(GetEditingObject());

	AddEditingObject(InPtr->Asset);
	DetailsView->SetObject(InPtr->Asset);
}