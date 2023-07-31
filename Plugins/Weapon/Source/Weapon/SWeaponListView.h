#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
//��ư���� �͵��� ��� Widget��, �̸� �տ� S �����͵� ��κ��� Widget��.
//SCompoundWidget�� � �����۵��� ���̺� �������� �������ִ¾���.
//1���� �迭�̶�� ������ �Ʒ��� �����۵��� ���̴� ����� �ɰŰ�
//2���� �迭�̶�� �ٵ��� �������� ���� ���� �����۵��� ä������ ����� ��.
#include "Widgets/Views/STableRow.h"

//1���� �迭�� �ϳ��� ��Ұ� �� ����ü
struct FWeaponRowData
{
	int Index;   //���ȣ
	FString Context;   //��µ� ���� 
	class UCWeaponAsset* Asset;   //���� ������ ����

	//�� ����ü�� ������ 1
	FWeaponRowData()
	{

	}

	//�� ����ü�� ������ 2
	FWeaponRowData(int32 InIndex, FString InContext, class UCWeaponAsset* InAsset)
	{
		Index = InIndex;
		Context = InContext;
		Asset = InAsset;
	}

	//���������� ����Ʈ �����͸� ���� �������ִ� �Լ� (����� �����ͷ� ����ü �ٷ�� ���)
	static TSharedPtr<FWeaponRowData> Make(int32 InIndex, FString InContext,
		class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InIndex, InContext, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr; //Ÿ�Ը� �ʹ� �� Ÿ�Ը� ������

///////////////////////////////////////////////////////////////////////////////

typedef SListView<FWeaponRowDataPtr> SWeaponListViewRow; //�ؿ��� ����� ������. �� ������

//SWeaponListView �迭�� �������� ����·� ������������ ������ Ŭ���� 
//(���̺� �������� ����Ʈ�������� ����)
class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
	//���� ���� ���� ���̺� Row�� ����Ŷ� SMultiColumnTableRow �� ���� ����� ����.
{
public:
	//������Ʈ���� �ٸ������� �����͸� �Ѱ��ֱ� ���ؼ� �������ִ°���. �� ���; ���� 2��° 20�� �κ�
	SLATE_BEGIN_ARGS(SWeaponTableRow) {} //������Ʈ�� Argument�� �����ϱ� �����ϰڴ�.
	SLATE_ARGUMENT(FWeaponRowDataPtr, Row)
		SLATE_END_ARGS() //������Ʈ�� Argument ���Ǹ� �����ڴ�.

public:
	//SWeaponListView Ŭ���� Construct���� �� Construct�� ȣ���ؼ� �����Ұ���.
	void Construct(const FArguments& InArgs,
		const TSharedRef<STableViewBase>& OwnerTableView);

protected:
	//�θ��� ���������Լ� ������. �Լ����� Create�� ��ü�� �����Ѵٴ� �ǹ̸� ������
	//Generate �� ������ �����͸� �����Ѵٴ� �ǹ̸� ������ ����.
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Row; //���� �ڽ��� ���� ������ ������
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
	//������Ʈ Ŭ������ ���鶧�� ������, �Ҹ��ڰ� �ʿ����. 
	//SN ew(��ũ����)�� S�� ���� ��ü�� �����ϰ�, Construct �Լ��� ����.
	//��� ������Ʈ�� �� Construct �Լ��� ������ �ְ�, �̰� ������ ������ ��.
	void Construct(const FArguments& InArgs);

public:
	bool HasDataPtrs() { return RowDatas.Num() > 0; }
	FWeaponRowDataPtr GetRowDataPtrByName(FString InName);
	FWeaponRowDataPtr GetFirstDataPtr() { return RowDatas[0]; }

	void SelectDataPtr(class UCWeaponAsset* InAsset);
	FString SelectedRowDataPtrName();


private:
	//OnGenerateRow �������̼ǿ��� ����� ��
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
	TArray<FWeaponRowDataPtr> RowDatas; //�迭 ����

	//TSharedPtr<SListView<FWeaponRowDataPtr>>  : FWeaponRowDataPtr�� �ٷ�� ����Ʈ�� 
	//                                            SListView�� ����� �����ͷ� �ٷ����.
	//�̷��� �ʹ� �����غ��̴ϱ� SListView<FWeaponRowDataPtr>�� ������ ��������. 
	//SWeaponListViewRow��
	TSharedPtr<SWeaponListViewRow> ListView;
	//���� �迭 �����ʹ� RowDatas ������, ��� ���������� ListView�� �����ϴ°���.
	//ListView ����� �����Ͱ� �迭���� ��ҵ��� �����Ұ���.


	FText SearchText;
	TSharedPtr<SSearchBox> SearchBox;
};