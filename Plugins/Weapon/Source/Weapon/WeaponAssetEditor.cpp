#include "WeaponAssetEditor.h"
#include "Widgets/Docking/SDockTab.h"

#include "WeaponDetailsView.h"
#include "WeaponEquipmentData.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "ListView";  //왼쪽 창 이름.
const FName FWeaponAssetEditor::DetailsTabId = "Details";  //오른쪽 창 이름

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	//이미 창이 있으면 창 닫고 리셋해준다음에 새로 여는거임. 
	if (Instance.IsValid())
	{
		if(Instance->ListView.IsValid())
		{
			//창 열림, 리스트 뷰 아이템 선택
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
			//컨텐츠 브라우저 선택 상황
			Instance->CloseWindow();
			Instance.Reset();
			Instance = nullptr;

		}
	}

	//Instance는 싱글톤이라 하나만 존재하고 OpenWindow 함수가 콜 될때 생성됨.
	Instance = MakeShareable(new FWeaponAssetEditor());
	//내부에서 사용하는 Open 함수를 호출해서 창을 띄워줌.
	Instance->Open(InAssetName);
}

//창이 열렸을때 정의해줘야하는 것들을 담은 함수
void FWeaponAssetEditor::Open(FString InAssetName)
{
	//왼쪽 탭 ListView 생성 -----------------------------------------------------------------------------------------------
	ListView = SNew(SWeaponListView)
		.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::WeaponListViewSelectedItem);
	//-------------------------------------------------------------------------------------------------------------------------

	//오른쪽 탭 DetailsView 생성 ---------------------------------------------------------------------------------------------------------

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//디테일 창이 열리기 전에 "EquipmentData" 타입을 FWeaponEquipmentData 인스턴스를 만들어서 등록해줌. 뒤에는 델리게이션 매개변수임. 
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
			//NewPrimaryArea 가 주 영역임. 이 영역을 분할하는거임. 
			//SetOrientation(Orient_Vertical) : 수직으로 가른다.
			//| 방향이 아닌 ㅡ 방향임. ㅡ 이렇게 나눠서 위쪽에 툴바를 배치 하고 
			//아래쪽을 또 두영역으로 가를거임.
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split   //영역을 나누는거임. 여기가 툴바영역 ==================
			(
				FTabManager::NewStack()  //여기서 새로운 영역을 생성하겠다는거임. 
				//Stack은 고정영역임.
				->SetSizeCoefficient(0.1f)  //영역의 크기 10프로 정도 사용하겠다. 
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			) //===============================================
			->Split  //툴바 밑 메인 영역 ================================================
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split //왼쪽 영역 --------------------------------------
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f)
					->AddTab(ListViewTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				) //-----------------------------------------------------
				->Split //오른쪽 영역 ------------------------------------
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f)
					->AddTab(DetailsTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				) //-----------------------------------------------------
			)//========================================================================

		);

	//WeaponAssetEditor 창을 여는 두가지 경우 
	//1번 : 콘텐츠 브라우저에 있는 WeaponAsset을 여는 경우 ( 예를 들어 DA_Fist 를 더블 클릭해서 여는 경우)
	//2번 : 어떠한 WeaponAsset도 선택하지 않고 그저 툴바에 있는 Weapon 버튼을 눌러서 창을 여는경우.

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

//창을 닫을때
bool FWeaponAssetEditor::OnRequestClose()
{
	FWeaponEquipmentData::RemoveCheckBoxes();

	if(DetailsView.IsValid())
	{
		if (!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);
	}

	//PropertyEditor 모듈이 불려졌는지를 일단 확인하고
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

//탭을 Spawn 시키는 애를 등록시키겠다 라는 함수임. 부모함수 재정의한거
//탭을 정의 하는 부분. Id로 구분해서 탭들을 정의함.
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

//생성한 디테일 창을 컨텐츠 영역에 추가해주면됨. 
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