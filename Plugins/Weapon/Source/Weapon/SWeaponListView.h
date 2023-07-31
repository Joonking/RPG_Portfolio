#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
//버튼같은 것들은 모두 Widget임, 이름 앞에 S 붙은것들 대부분이 Widget임.
//SCompoundWidget은 어떤 아이템들을 테이블 형식으로 관리해주는애임.
//1차원 배열이라면 위에서 아래로 아이템들이 놓이는 방식이 될거고
//2차원 배열이라면 바둑판 형식으로 가로 세로 아이템들이 채워지는 방식이 됨.
#include "Widgets/Views/STableRow.h"

//1차원 배열에 하나의 요소가 될 구조체
struct FWeaponRowData
{
	int Index;   //행번호
	FString Context;   //출력될 내용 
	class UCWeaponAsset* Asset;   //실제 편집할 에셋

	//이 구조체의 생성자 1
	FWeaponRowData()
	{

	}

	//이 구조체의 생성자 2
	FWeaponRowData(int32 InIndex, FString InContext, class UCWeaponAsset* InAsset)
	{
		Index = InIndex;
		Context = InContext;
		Asset = InAsset;
	}

	//내부적으로 스마트 포인터를 만들어서 리턴해주는 함수 (쉐어드 포인터로 구조체 다루는 방식)
	static TSharedPtr<FWeaponRowData> Make(int32 InIndex, FString InContext,
		class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InIndex, InContext, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr; //타입명 너무 길어서 타입명 재정의

///////////////////////////////////////////////////////////////////////////////

typedef SListView<FWeaponRowDataPtr> SWeaponListViewRow; //밑에서 사용할 변수임. 길어서 재정의

//SWeaponListView 배열에 아이템이 어떤형태로 보여지질지를 결정할 클래스 
//(테이블 형태인지 리스트형태인지 같은)
class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
	//여러 열을 가진 테이블 Row를 만들거라 SMultiColumnTableRow 로 부터 상속을 받음.
{
public:
	//슬레이트에서 다른곳으로 데이터를 넘겨주기 위해서 정의해주는거임. 좀 어렵; 강의 2번째 20분 부분
	SLATE_BEGIN_ARGS(SWeaponTableRow) {} //슬레이트의 Argument를 정의하기 시작하겠다.
	SLATE_ARGUMENT(FWeaponRowDataPtr, Row)
		SLATE_END_ARGS() //슬레이트의 Argument 정의를 끝내겠다.

public:
	//SWeaponListView 클래스 Construct에서 이 Construct를 호출해서 생성할거임.
	void Construct(const FArguments& InArgs,
		const TSharedRef<STableViewBase>& OwnerTableView);

protected:
	//부모의 순수가상함수 재정의. 함수명에서 Create는 객체를 생성한다는 의미를 가지고
	//Generate 는 보여질 데이터를 생성한다는 의미를 가지고 있음.
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Row; //실제 자신의 행이 보여질 데이터
};

///////////////////////////////////////////////////////////////////////////////

DECLARE_DELEGATE_OneParam(FOnWeaponListViewSelectedItem, FWeaponRowDataPtr);

class WEAPON_API SWeaponListView
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponListView) {}
	SLATE_EVENT(FOnWeaponListViewSelectedItem, OnWeaponListViewSelectedItem)
		SLATE_END_ARGS()

public:
	//슬레이트 클래스를 만들때는 생성자, 소멸자가 필요없음. 
	//SN ew(매크로임)는 S에 대한 객체를 생성하고, Construct 함수를 콜함.
	//모든 슬레이트는 이 Construct 함수를 가지고 있고, 이게 생성자 역할을 함.
	void Construct(const FArguments& InArgs);

public:
	bool HasDataPtrs() { return RowDatas.Num() > 0; }
	FWeaponRowDataPtr GetRowDataPtrByName(FString InName);
	FWeaponRowDataPtr GetFirstDataPtr() { return RowDatas[0]; }

	void SelectDataPtr(class UCWeaponAsset* InAsset);
	FString SelectedRowDataPtrName();


private:
	//OnGenerateRow 델리게이션에서 사용할 함
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow,
		const TSharedRef<STableViewBase>& InTable);

	FText GetAssetCount() const;

	void OnTextChanged(const FText& InText);
	void OnTextCommitted(const FText& InText, ETextCommit::Type InType);

	void OnSelectionChanged(FWeaponRowDataPtr InPtr, ESelectInfo::Type InType);

private:
	void ReadAssets();

private:
	FOnWeaponListViewSelectedItem OnWeaponListViewSelectedItem;

private:
	TArray<FWeaponRowDataPtr> RowDatas; //배열 변수

	//TSharedPtr<SListView<FWeaponRowDataPtr>>  : FWeaponRowDataPtr를 다루는 리스트인 
	//                                            SListView를 쉐어드 포인터로 다룰거임.
	//이러면 너무 복잡해보이니까 SListView<FWeaponRowDataPtr>를 위에서 재정의함. 
	//SWeaponListViewRow로
	TSharedPtr<SWeaponListViewRow> ListView;
	//실제 배열 데이터는 RowDatas 이지만, 어떻게 보여질지는 ListView가 결정하는거임.
	//ListView 쉐어드 포인터가 배열안의 요소들을 관리할거임.


	FText SearchText;
	TSharedPtr<SSearchBox> SearchBox;
};