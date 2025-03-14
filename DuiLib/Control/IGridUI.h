#pragma once


namespace DuiLib
{

#define MAX_GRID_COLUMN_COUNT	64


typedef enum emGridCellType
{
	celltypeText			= 0,
	celltypeEdit			= 1,
	celltypeCheckBox		= 2,
	celltypeCombo			= 3,
	celltypeDateTime		= 4,
	celltypeDate			= 5,
	celltypeTime			= 6,
	celltypePicture			= 7,
	celltypeContainer		= 8
}GridCellType;

struct TCellID
{
	int row;
	int col;
	bool IsValid() { return row >= 0 && col >= 0 && col < MAX_GRID_COLUMN_COUNT; }
};

struct TGridMergeRange
{
	int begin_row;
	int end_row;
	int begin_col;
	int end_col;
};

//单元格数据, 扩展这个类，注意综合考虑 内存占用 和 运行速度。
class UILIB_API TCellData : public ILinkedList
{
	friend class IGridUI;
public:
	TCellData();

protected:
	void Select(BOOL bSelected=TRUE);

public:
	BOOL IsSelected() const;

	void SetCheckBoxCheck(BOOL bSelected=TRUE);
	BOOL IsCheckBoxCheck() const;

	void SetMergedWidthOthers(bool bMerged);
	bool IsMergedWithOthers() const;

	void SetNeedPaint(bool bNeedPaint);
	bool IsNeedPaint() const;

	CDuiString GetText() const;
	int GetTextN() const;

	void SetText(LPCTSTR pstrText);
	void SetTextN(int n);
	void SetTextV(LPCTSTR lpszFormat, ...);

	void SetTag(UINT_PTR tag);
	UINT_PTR GetTag() const;

	void SetTextColor(DWORD dwColor);
	DWORD GetTextColor() const;
protected:
	CDuiString m_sText;
	UINT_PTR m_tag;

	//bt0 = 单元格是否选中
	//bt1 = 单选框选中状态
	//bt2 = IsMergedWidthOthers 是否被合并
	//bt3 = 是否需要绘制
	BYTE m_state;

	DWORD m_dwTextColor;
};

//表格行数据
struct UILIB_API TRowData : public ILinkedList
{
	TRowData();

	void SetHeight(int n);
	int  GetHeight() const;

	void Selected(BOOL bSelected=TRUE);
	BOOL IsSelected() const;

	void SetTag(UINT_PTR tag);
	UINT_PTR GetTag() const;

	TCellData *GetCell(int col);

	short m_nHeight;
	BOOL m_bSelected;
	UINT_PTR m_tag;
	CStdPtrArray m_cells;
};

class UILIB_API IGridUI
{
public:
	IGridUI(void);
	virtual ~IGridUI(void);

	virtual void SendGridNotify(LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false) = 0;

	virtual void Refresh(bool bNeedUpdate=false)		= 0;

	virtual void SetVirtualGrid(BOOL bVirtual)	= 0;
	BOOL IsVirtualGrid()						{ return m_bVirtualGrid; }

	virtual BOOL SetRowCount(int rows)			= 0;
	virtual int GetRowCount()					= 0;

	virtual BOOL SetColumnCount(int cols)		= 0;
	virtual int GetColumnCount()				= 0;

	virtual BOOL SetFixedRowCount(int rows)	= 0;
	virtual int GetFixedRowCount()				= 0;

	virtual void SetFixedColumnCount(int cols)	{ m_nFixedColCount = cols; }
	virtual int GetFixedColumnCount()			{ return m_nFixedColCount; }

	virtual void SetViewListNumber(BOOL bView)		{ m_bViewListNo = bView; }
	virtual BOOL IsViewListNumber()					{ return m_bViewListNo; }

	void SetDefRowHeight(int height)			{ m_nDefRowHeight = height; }
	int GetDefRowHeight() const					{ return m_nDefRowHeight; }
	void SetDefColWidth(int width)				{ m_nDefColWidth = width; }
	int GetDefColWidth() const					{ return m_nDefColWidth; }

	void EnableDrawRowLine(BOOL bEnable)		{ m_bDrawRowLine = bEnable; }
	BOOL IsDrawRowLine()						{ return m_bDrawRowLine; }

	void EnableDrawColumnLine(BOOL bEnable)		{ m_bDrawColumnLine = bEnable; }
	BOOL IsDrawColumnLine()						{ return m_bDrawColumnLine; }

	void SetLineColor(DWORD clr)				{ m_dwLineColor = clr; }
	DWORD GetLineColor() const					{ return m_dwLineColor; }

	virtual BOOL SetRowHeight(int row, int height)		= 0;
	virtual int  GetRowHeight(int row, BOOL bScaleByDPI=FALSE)					= 0;

	virtual BOOL SetColumnWidth(int col, int width)	= 0;
	virtual int  GetColumnWidth(int col, BOOL bScaleByDPI=FALSE)				= 0;

	void EnableSizeColumn(BOOL bEnable)			{ m_bEnableSizeColumn = bEnable; }
	BOOL IsEnableSizeColumn()					{ return m_bEnableSizeColumn; }

	void EnableSizeRow(BOOL bEnable)			{ m_bEnableSizeRow = bEnable; }
	BOOL IsEnableSizeRow()						{ return m_bEnableSizeRow; }

	void SetExpandColumnByText(BOOL bExpand)	{ m_bAutoExpandColumnByText = bExpand; }
	BOOL IsExpandColumnByText()				{ return m_bAutoExpandColumnByText; }

	void SetExpandLastColumn(BOOL bExpand)		{ m_bAutoExpandLastColumn = bExpand; }
	BOOL IsExpandLastColumn()					{ return m_bAutoExpandLastColumn; }

	void SetFitColumns(BOOL bFit)		{ m_bAutoFitColumns = bFit; }
	BOOL IsFitColumns()					{ return m_bAutoFitColumns; }

	void SetFitRows(BOOL bFit)			{ m_bAutoFitRows = bFit; }
	BOOL IsFitRows()						{ return m_bAutoFitRows; }

	void SetListMode(BOOL bList)				{ m_bListMode = bList; }
	BOOL IsListMode()							{ return m_bListMode; }

	void SetSingleRowSelection(BOOL bSingle)	{ m_bSingleRowSelection = bSingle; }
	BOOL IsSingleRowSelection()					{ return m_bSingleRowSelection; }

	void SetCheckBoxSelection(BOOL bSingle)		{ m_bCheckBoxSelection = bSingle; }
	BOOL IsCheckBoxSelection()					{ return m_bCheckBoxSelection; }

	void SetHeaderSort(BOOL bSort)				{ m_bHeaderSort = bSort; }
	BOOL IsHeaderSort()	const					{ return m_bHeaderSort; }

	void SetSortAscendingImage(LPCTSTR lpszImage)	{ m_sSortAscendingImage = lpszImage; }		
	LPCTSTR GetSortAscendingImage()					{ return m_sSortAscendingImage; }

	void SetSortDescendingImage(LPCTSTR lpszImage)	{ m_sSortDescendingImage = lpszImage; }		
	LPCTSTR GetSortDescendingImage()				{ return m_sSortDescendingImage; }

	void SetSortIconSize(SIZE sz)				{ m_szSortIconSize = sz; }
	SIZE GetSortIconSize()						{ return m_szSortIconSize; }

	void SetEditable(BOOL bEditable)			{ m_bEditable = bEditable; }
	BOOL GetEditable() const					{ return m_bEditable; }

	//////////////////////////////////////////////////////////////////////////
	void SetStyleFixedRow(LPCTSTR pstrValue)			{ m_sStyleFixedRow = pstrValue; }
	LPCTSTR GetStyleFixedRow()							{ return m_sStyleFixedRow; }
	void SetStyleFixedCell(LPCTSTR pstrValue)			{ m_sStyleFixedCell = pstrValue; }
	LPCTSTR GetStyleFixedCell()							{ return m_sStyleFixedCell; }

	void SetStyleRow(LPCTSTR pstrValue)				{ m_sStyleRow = pstrValue; }
	LPCTSTR GetStyleRow()							{ return m_sStyleRow; }
	void SetStyleCell(LPCTSTR pstrValue)			{ m_sStyleCell = pstrValue; }
	LPCTSTR GetStyleCell()							{ return m_sStyleCell; }

	void SetStyleEdit(LPCTSTR pstrValue)			{ m_sStyleEdit = pstrValue; }
	LPCTSTR GetStyleEdit()							{ return m_sStyleEdit; }
	void SetStyleCheckBox(LPCTSTR pstrValue)		{ m_sStyleCheckBox = pstrValue; }
	LPCTSTR GetStyleCheckBox()						{ return m_sStyleCheckBox; }
	void SetStyleCombo(LPCTSTR pstrValue)			{ m_sStyleCombo = pstrValue; }
	LPCTSTR GetStyleCombo()							{ return m_sStyleCombo; }
	void SetStyleDateTime(LPCTSTR pstrValue)		{ m_sStyleDateTime = pstrValue; }
	LPCTSTR GetStyleDateTime()						{ return m_sStyleDateTime; }
	void SetStyleDate(LPCTSTR pstrValue)			{ m_sStyleDate = pstrValue; }
	LPCTSTR GetStyleDate()							{ return m_sStyleDate; }
	void SetStyleTime(LPCTSTR pstrValue)			{ m_sStyleTime = pstrValue; }
	LPCTSTR GetStyleTime()							{ return m_sStyleTime; }
	void SetStylePicture(LPCTSTR pstrValue)			{ m_sStylePicture = pstrValue; }
	LPCTSTR GetStylePicture()						{ return m_sStylePicture; }

protected:
	BOOL  m_bVirtualGrid;				//virtual grid

	int   m_nDefRowHeight;				//default row's height
	int   m_nDefColWidth;				//default column's width
	BOOL  m_bViewListNo;				//view list index on leftmost fixed column
	int	  m_nFixedColCount;				//count of the fixed columns on the left side by grid

	BOOL  m_bDrawRowLine;				//enable drawing row's line
	BOOL  m_bDrawColumnLine;			//enable drawing column's line
	DWORD m_dwLineColor;				//grid line color

	BOOL  m_bEnableSizeColumn;			//enable drag column size in grid header
	BOOL  m_bEnableSizeRow;				//enable drag row height in grid header

	BOOL  m_bAutoExpandColumnByText;	//enable auto expand the column's with by text
	BOOL  m_bAutoExpandLastColumn;		//enable auto expand the last of column's with  to fit list
	BOOL  m_bAutoFitColumns;			//enable auto expand width of columns  to fit list
	BOOL  m_bAutoFitRows;				//enable auto expand height of rows  to fit list
		
	BOOL  m_bListMode;					//click to select a full row
	BOOL  m_bSingleRowSelection;		//only single row can be selected, not multi rows selected.
	BOOL  m_bCheckBoxSelection;			//列表模式下选中行时，联动最左边的非固定列checkbox单元格。


	BOOL  m_bHeaderSort;				//enable click fixed row to sort column
	CDuiString m_sSortAscendingImage;	//ascending icon
	CDuiString m_sSortDescendingImage;	//descending icon
	SIZE m_szSortIconSize;

	BOOL m_bEditable;

	CDuiString m_sStyleFixedRow;
	CDuiString m_sStyleFixedCell;
	CDuiString m_sStyleRow;
	CDuiString m_sStyleCell;
	CDuiString m_sStyleEdit;
	CDuiString m_sStyleCheckBox;
	CDuiString m_sStyleCombo;
	CDuiString m_sStyleDateTime;
	CDuiString m_sStyleDate;
	CDuiString m_sStyleTime;
	CDuiString m_sStylePicture;

public:
	TRowData *AllocRowData();
	void FreeRowData(TRowData *pRowData);
	TCellData *AllocCellData();
	void FreeCellData(TCellData *pCellData);

	TRowData *GetRowData(int row);
	TRowData &Row(int row);

	TCellData *GetCellData(int row, int col);
	TCellData *GetCellData(const TCellID &cell);
	TCellData &Cell(int row, int col);
	TCellData &Cell(const TCellID &cell);

	virtual void ClearSelectedRows();
	virtual void SelectRow(int row, BOOL bSelected=TRUE, BOOL bTriggerEvent= FALSE);
	BOOL IsSelectedRow(int row);

	void ClearSelectedCells();
	void SelectCell(int row, int col, BOOL bSelected=TRUE, BOOL bTriggerEvent = FALSE);
	BOOL IsSelectedCell(int row, int col);

	int GetSelectRowCount();
	int GetSelectRow();
	int GetNextSelectRow();

	int GetSelectCellCount();
	TCellID GetSelectCell();
	TCellID GetNextSelectCell();

	virtual void SetFocusCell(int row, int col) = 0;
	virtual void SetFocusCell(const TCellID &cellID) = 0;
	virtual const TCellID &GetFocusCell() const = 0;
protected:
	CStdPtrArray m_RowData; //保存表格数据

	std::map<INT64, TCellID> m_aSelectedCells; //保存选中的单元格，存储TCellID. key: 高32位保存行号，低32位保存列号
	std::map<INT64, TCellID>::iterator m_iteratorCell;

	std::map<INT, INT> m_aSelectedRows; //保存选中的行，存储行号.  key:行号
	std::map<INT, INT>::iterator m_iteratorRow;

	TCellID m_FocusCell;

	std::map<INT64, GridCellType> m_mapCellType;	//保存单元格类型，对单个格子设置特殊的类型，优先级高于整列设置类型
	std::map<INT64, TGridMergeRange>	m_mapCellMergeRange;	//保存单元格合并区域
};



}