#include "SWeaponListView.h"
#include "EngineUtils.h"
#include "Widgets/Input/SSearchBox.h"

#include "Weapons/CWeaponAsset.h"

//항상 Construct는 보여질 모양을 결정하는 곳이라고 생각하면 됨. 슬레이트의 생성자.
void SWeaponTableRow::Construct(const FArguments& InArgs,
	const TSharedRef<STableViewBase>& OwnerTableView)
{
	Row = InArgs._Row;

	SMultiColumnTableRow<FWeaponRowDataPtr>::Construct
	(
		FSuperRowType::FArguments().Style(FEditorStyle::Get(), "TableView.DarkRow"),
		OwnerTableView
	);
}

TSharedRef<SWidget> SWeaponTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	FString str;
	if (InColumnName == FName("Index"))
		str = FString::FromInt(Row->Index);
	else if (InColumnName == FName("Context"))
		str = Row->Context;

	FString toolTip;
	if (!!Row->Asset)
		toolTip = Row->Asset->GetPathName();

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(str))
		.ToolTipText(FText::FromString(toolTip))
		];
}

///////////////////////////////////////////////////////////////////////////////

void SWeaponListView::Construct(const FArguments& InArgs)
{
	OnWeaponListViewSelectedItem = InArgs._OnWeaponListViewSelectedItem;

	ChildSlot //슬롯은 컨텐츠일수도 아닐수도 있음. 
		[
			SNew(SVerticalBox)  //행으로 긴 박
			+ SVerticalBox::Slot()   //슬롯은 +로 추가할 수 있음. 
		.AutoHeight()
		.Padding(2, 0)
		[
			SNew(SBox)
			[
				SAssignNew(SearchBox, SSearchBox)
				.SelectAllTextWhenFocused(true)
		.OnTextChanged(this, &SWeaponListView::OnTextChanged)
		.OnTextCommitted(this, &SWeaponListView::OnTextCommitted)
			]
		]
	+ SVerticalBox::Slot()
		.FillHeight(1)   //내용을 최대 높이까지 채움. 
		[
			//배열 안에서 SNew매크로로 생성할 수 없으니, 이럴때는 SAssignNew 매크로를 사용함. 
			SAssignNew(ListView, SWeaponListViewRow)  //ListView에 SWeaponListViewRow을 할당해라.
			.ListItemsSource(&RowDatas)  //어떤 데이터를 출력할지 
		.OnGenerateRow(this, &SWeaponListView::OnGenerateRow) //어떻게 보여줄지 (델리게이션임)
		//만약 ListItemsSource에 데이터 RowDatas가 10개면 OnGenerateRow 델리게이션에 붙은
		//OnGenerateRow 함수가 10번 호출됨. 각 행에 따라 (행 마다 모양을 결정하는거임)
		.OnSelectionChanged(this, &SWeaponListView::OnSelectionChanged)
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Index")
			.DefaultLabel(FText::FromString(""))
			.ManualWidth(50)
			+ SHeaderRow::Column("Context")
			.DefaultLabel(FText::FromString("Asset Name"))
		)
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(FMargin(8, 2))
		[
			SNew(STextBlock)
			.Text(this, &SWeaponListView::GetAssetCount)
		]
		]
		];

	ReadAssets();
}



//Asset들을 불러오는 함수 
void SWeaponListView::ReadAssets()
{
	RowDatas.Empty();  //배열 초기


	TArray<UObject*> objects; //Asset은 전부 UObject로 상속 받으니까 
	EngineUtils::FindOrLoadAssetsByPath("/Game/Weapons/", objects, EngineUtils::ATL_Regular);
	//FindOrLoadAssetsByPath : 에셋을 불러주는 함수,  경로가서 에셋을 불러서 objects에 넣어줌.
	//마지막 매개변수 EngineUtils::ATL_Class - 블루프린트 타입을 불러올때, 
	//               EngineUtils::ATL_Regular - 에셋을 불러올때

	int32 index = 0;
	for (UObject* obj : objects)  //불러온 에셋들을 CWeaponAsset으로 캐스팅해서 거름 
	{
		UCWeaponAsset* asset = Cast<UCWeaponAsset>(obj);
		if (asset == nullptr) continue;

		FString name = asset->GetName();
		if (SearchText.IsEmpty() == false)
		{
			if (name.Contains(SearchText.ToString()) == false)
				continue;
		}

		RowDatas.Add(FWeaponRowData::Make(++index, name, asset));
	}

	//정렬
	RowDatas.Sort([](const FWeaponRowDataPtr& A, const FWeaponRowDataPtr& B)
		{
			return A->Index < B->Index;
		});

	ListView->RequestListRefresh();
}


//행의 모양을 결정할 함수. 델리게이션 OnGenerateRow에 의해 호출됨. 
TSharedRef<ITableRow> SWeaponListView::OnGenerateRow(FWeaponRowDataPtr InRow,
	const TSharedRef<STableViewBase>& InTable)
{
	return SNew(SWeaponTableRow, InTable).Row(InRow);
}

FText SWeaponListView::GetAssetCount() const
{
	FString str = FString::Printf(L"%d Assets", RowDatas.Num());

	return FText::FromString(str);
}

void SWeaponListView::OnTextChanged(const FText& InText)
{
	if (SearchText.CompareToCaseIgnored(InText) == 0)
		return;

	SearchText = InText;
	ReadAssets();
}

void SWeaponListView::OnTextCommitted(const FText& InText, ETextCommit::Type InType)
{
	OnTextChanged(InText);
}

void SWeaponListView::OnSelectionChanged(FWeaponRowDataPtr InPtr, ESelectInfo::Type InType)
{
	if (InPtr == nullptr) return;
	if (InPtr->Asset == nullptr) return;

	OnWeaponListViewSelectedItem.ExecuteIfBound(InPtr);
}

FWeaponRowDataPtr SWeaponListView::GetRowDataPtrByName(FString InName)
{
	if (HasDataPtrs() == false)
		return nullptr;

	for(FWeaponRowDataPtr ptr : RowDatas)
	{
		if (ptr->Context == InName)
			return ptr;
	}

	return nullptr;
}

void SWeaponListView::SelectDataPtr(UCWeaponAsset* InAsset)
{
	if (HasDataPtrs() == false)
		return;

	for (FWeaponRowDataPtr ptr : RowDatas)
	{
		if (ptr->Asset == InAsset)
		{
			ListView->SetSelection(ptr);
			return;
		}
	}
}

FString SWeaponListView::SelectedRowDataPtrName()
{
	TArray<FWeaponRowDataPtr> ptrs = ListView->GetSelectedItems();

	if (ptrs.Num() > 0)
		return ptrs[0]->Asset->GetName();

	return "";
}
