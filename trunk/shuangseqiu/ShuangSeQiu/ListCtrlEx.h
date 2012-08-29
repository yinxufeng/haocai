#pragma once
#include "SkinHeaderCtrl.h"
#include <map>
#include <vector>
using std::vector;
using std::map;

/****************************************************************************
*  描述：　增强型列表控件                                                   *
*　创建：　2011.6.20                                                        *
*  作者：  谭军红                                                           *
*                                                                           *
****************************************************************************/

//自定义消息
#define WM_LIST_BUTTON_CLICK WM_USER + 5000             //按钮点击消息
#define WM_VIRTUAL_LIST_MSG  WM_USER + 5001             //虚模式下消息 : wParam 标示ID , lParam 显示的开始行
#define WM_LIST_CHECKBOX_CLICK  WM_USER + 5002				//勾选框选中事件

//列类型
enum eItemType
{
	TEXT_TYPE,                           //文本类型
	BUTTON_TYPE,                         //按钮类型               
	CHECK_BOX_TYPE,                      //复习选框类型
	IMGE_TYPE,                           //图片类型
	CHECKBOX_IMAGE_AND_TEXT_TYPE,        //有图片，有文字，有复选框类型
	IMAGE_AND_TEXT_TYPE,                  //有图片和文字类型
	PROGRESS_AND_TEXT_TYPE					//进度条带文字
};

//绘制风格
enum eDrawStyle
{
	TEXT_LEFT_IMAGE_RIGHT,              //文字在图片右边
	TEXT_RIGHT_IMAGE_LEFT,              //文字在图片左边 
	TEXT_UP_IMAGE_DOWN,                 //文字在图片下边
	TEXT_DOWN_IMAGE_UP,                 //文字在图片下边
	TEXT_ON_IMAGE                       //文字在图片上边
};

//填充模式
enum eFillMode {
	MODE_FILL_RGB,        //以RGB填充
	MODE_FILL_IMG,        //以图片填充
	MODE_FILE_NO          //不填充
};

struct sItemBkData
{
	eFillMode m_BkFillMode;      //背景填充方式 M
	COLORREF  m_BkColor;         //背景颜色
	Image*    m_Image;           //背景图片
	eFillMode m_HeightFillMode; //是否高亮 MODE_FILL_NO 无高亮
	COLORREF m_HeightColor;     //高亮颜色
	Image*   m_HeightImage;     //高亮图片
	sItemBkData()
	{
		m_BkFillMode = MODE_FILE_NO;
		m_BkColor = RGB(255,255,255);
		m_Image   = NULL;

		m_HeightFillMode = MODE_FILE_NO;
		m_HeightColor = RGB(150,205,205);
		m_HeightImage = NULL;
	}
};

//Item 特定风格数据结构
struct sItemStyle
{
	struct sTextData                          //文本数据
	{
		COLORREF   m_TextColor;                //文本
		BOOL       m_EnableEdit;               //是否可编辑    //目前只有在 TEXT_TYPE 下可编辑
		CFont*     m_TextFont;                 //文本字体
		UINT       m_TextFormat;               //文本显示风格 同DrawText中的Format
	};

	struct sButtonData                        //按钮数据
	{
		BOOL      m_IsNormal;                 //是否处于正常状态
		Image*    m_ButtonNormalImage;        //按钮正常状态图片
		Image*    m_ButtonActiveImage;        //按钮活动状态图片
		BOOL      m_HasText;                  //是否具有文本
	    sTextData m_TextData;                 //当m_HasText为TRUE时，此字段才有效
	};

	struct sCheckBoxData                      //复选框数据
	{
		BOOL   m_IsCheck;                     //是否处于选中状态
		Image* m_CheckBoxUnSelectedImage;     //复选框未选中状态图片
		Image* m_CheckBoxSelectedImage;       //复选框选中状态图片
		BOOL      m_HasText;                  //是否具有文本
	    sTextData m_TextData;                 //当m_HasText为TRUE时，此字段才有效
		eDrawStyle m_DrawStyle;               //绘制风格，当m_HasText为TRUE时,此字段才有效
	};

	struct sImageData                         //图片数据
	{
		BOOL   m_IsNormal;                    //是否处于正常状态
		Image* m_NormalImage;                 //正常状态图片
		Image* m_ActiveImage;                 //活动状态图片
		BOOL   m_IsTouchClickMsg;             //是否触发点击消息    
		BOOL   m_IsDeleteNormalImage;         //是否删除图片
		BOOL   m_IsDeleteActiveImage;         //是否删除图片
		
	};
	struct sCheckBoxImageAndTextData          //复选框图片和文字数据
	{
		sCheckBoxData m_BoxData;              //复选框数据
		sTextData     m_TextData;             //文本数据
		sImageData    m_ImageData;            //图片数据
		eDrawStyle    m_DrawStyle;            //绘制风格
	};

	struct sImageAndTextData
	{
		eDrawStyle   m_DrawStyle;             //绘制风格
		sTextData    m_TextData;              //文本数据
		sImageData   m_ImageData;             //图片数据
	};

	union uDrawData
	{
		sTextData                    m_TextData;
		sButtonData                  m_ButtonData;
		sCheckBoxData                m_CheckBoxData;
		sImageData                   m_ImageData;
		sCheckBoxImageAndTextData    m_CheckBoxImageAndTextData;
		sImageAndTextData            m_ImageAndTextData;
	};

	struct sItemPos
	{
		int m_RowIndex;
		int m_ColoumIndex;
	};
	
	

	eItemType   m_ItemType;         //Item类型
	uDrawData   m_DrawData;         //Item画图数据

	sItemStyle()
	{
		memset(&m_DrawData,0,sizeof(uDrawData));
		m_ItemType = TEXT_TYPE;
		m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
		m_DrawData.m_TextData.m_EnableEdit = false;
		m_DrawData.m_TextData.m_TextFont = NULL;
		m_DrawData.m_TextData.m_TextFormat = DT_SINGLELINE | DT_CENTER| DT_VCENTER | DT_END_ELLIPSIS;
	}
};

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();

	virtual ~CListCtrlEx();

	//删除所有
	BOOL DeleteAllItems();

	//删除所有列
	BOOL DeleteAllColumn();

	//删除所有列风格
	void DeleteAllColumnStyle();

	//删除所有行风格
	void DeleteAllItemStyle();

	//删除列
	BOOL DeleteColumnStyle(int ColumIndex);
 
	//删除行
	BOOL DeleteItemStyle(int RowIndex);
	
	//设置复合框状态
	BOOL SetCheck(int RowIndex, BOOL Check = TRUE);

	//获取是否选择
	BOOL GetCheck(int RowIndex,int ColumIndex=0);

	//获取整体列显示风格
	 bool GetColumStyle(int ColumIndex,sItemStyle& Style);

	//获取特定单元显示风格
	bool GetItemSpeialStyle(int RowIndex, int ColumIndex, sItemStyle& Style);

	//设置整体列显示风格
	void SetColumStyle(int ColumIndex, sItemStyle& Style);

	//设置单元特定风格
	void SetItemSpecialStyle(int RowIndex,int ColoumIndex,sItemStyle& ItemStyle);

	//设置行高
	void SetRowHeight(int RowHeight);

	//获取行总数
	int GetRowCount(){ return m_RowCount; }

	//获取总列数
	int GetColmnCount() { return m_ColumnCount; }

	//插入列
	int InsertColumn(int nCol,LPCTSTR HeaderStr,int Format=LVCFMT_LEFT,int Width=-1,int Height=-1);

	//插入数据
	int InsertItem(int Item, LPCTSTR Str);

	//删除数据
	BOOL DeleteItem(int Item);

	//删除列
	BOOL DeleteColumn(int Col);

	//自绘函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//绘制子项
	virtual void DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem);

	//响应按钮按下消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//设置按钮响应窗口
	void SetButtonClickHwnd(HWND hWnd){ m_ButtonHwnd = hWnd;};
	
	//更改行高
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	
	//是否允许绘制垂直方向的线
	void EnableVecLine(BOOL DrawLine) { m_VecDrawLine = DrawLine;}

	//是否允许绘制横向方向的线
	void EnableHorLine(BOOL DrawLine) { m_HorDrawLine = DrawLine;}

	virtual void PreSubclassWindow();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//设置头部填充颜色
	void SetHeaderAndLineColor(COLORREF Color,COLORREF LineColor) { m_HeaderCtrl.m_DrawRGB = true;m_HeaderCtrl.m_BkColor = Color; m_HeaderCtrl.m_LineColor = LineColor;}

	//设置头部位图和分割线位图
	void SetHeaderAndLineImage(Image* HeaderIamge,Image* LineImage){ m_HeaderCtrl.m_DrawRGB= true;m_HeaderCtrl.m_pImageBg; m_HeaderCtrl.m_pImageLine = LineImage;}

	//是否显示头部
	void ShowHeader(BOOL Show) {m_HeaderCtrl.m_HeaderShow = Show;}

	//设置背景和选中行属性
	void SetItemBkData(sItemBkData BkData) {m_BkData = BkData; }

	//设置虚模式
	void SetVirtualMode(int VirtualID,BOOL IsVirtual){  m_VirtualID = VirtualID;m_IsVirtualMode = IsVirtual;}

	//触发当前位置：针对虚模式
	void TouchCurrentScrollPos();

	//设置当前选中行
	void SetCurrentSelectRow(int Row);
	//设置全选
	void SetAllLineSelected(int iRow);
	//设置选中属性
	void SetSelProperty(int iRow);

	//是否需要被删除
	bool bNeedDelete;

	//设置当前显示是否为视频
	void SetShowVideo(bool showVedio){m_ShowVedio = showVedio;};

	//
	void SetShowOther(bool showOther){m_ShowOther = showOther;};

	//屏蔽列表头移动事件
	afx_msg BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()

	//绘制背景
	virtual void DrawBkItem(CDC* pDC, int RowIndex,CRect Rect);

	//绘制
	virtual void DrawByStyle(CDC* pDC,int nItem,int nSubItem,CRect& rSubItem,sItemStyle* pStyle);

	//绘制视频
	virtual void DrawShowVedio(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, sItemStyle *pStyle);
	
	//获取图片绘制区域
	CRect GetImageDrawRect(Image* pImage,CRect Rect);

	//获取文本绘制区域
    CRect GetTextDrawRect(Image* pImage,CRect Rect,eDrawStyle Style);
	
	//获取文本和图片绘制区域
	void GetTextAndImageDrawRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style);

	//获取视频的绘图方式
	void GetVedioImageTextRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style);

	//获取图片绘制点
	CPoint GetImageDrawPoint(Image* pImage,CRect Rect);

	//Rect 到 RectF 的转换
	RectF RectToRectF(CRect Rect);

	//通过点查找当前位置
	bool FindRowAndColumnPos(CPoint Point,int& RowIndex,int& ColumnIndex,CRect& SubItemRect);

	//通过ItemId查询当前位置
	bool FindRowAndColumnPos(int ItemId,int& RowIndex,int& ColumnIndex);

	//显示编辑框
	void ShowEdit(CRect Rect,CString Str,CFont* Font);

	//动作
	bool OnButtonDownAction(sItemStyle* pStyle);

	//填充矩行区
	void FillRectByImage(CDC* pDC,Image* pImage,CRect Rect);

	//删除图片
	void DeleteImage(Image* pImage);

	//清除风格
	void CleanStyle(int ColumnIndex,sItemStyle* pStyle);

	struct sItemIndex
	{
		int  m_Index;
		bool m_IsDeleteFlag;
	};

	int                  m_RowCount;          //行数据
	int                  m_ColumnCount;       //列数
	map<long,sItemStyle> m_ItemStyleMap;      //特定单元风格映射表
	map<int,sItemStyle>  m_ColumnStyleMap;    //整体列风格表
	CEdit                m_Edit;              //编辑框
	COLORREF             m_LineColor;         //绘制线颜色
	sItemBkData          m_BkData;            //背景和高亮数据
	int                  m_CurrentSelectRow;  //当前选择行
	int					 m_OldSelectRow;	  //之前选中行
	HWND                 m_ButtonHwnd;        //按钮消息接收窗口句柄
	int                  m_RowHeight;         //行高
	BOOL                 m_VecDrawLine;       //是否允许绘制垂直方向的线
	BOOL                 m_HorDrawLine;       //是否允许绘制横向方向的线
	BOOL                 m_IsVirtualMode;     //是否为虚模式
	int                  m_VirtualID;         //虚模式ID
	CSkinHeaderCtrl      m_HeaderCtrl;        //头部控件
	
	vector<sItemIndex>   m_RowIndex;          //行索引
	vector<sItemIndex>   m_ColumnIndex;       //列索引

	bool     m_ShowVedio;
	bool     m_ShowOther;
	//listCtrl控件头
	//CSkinHeadCtrl m_skinHead;

	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


