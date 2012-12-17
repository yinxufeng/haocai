#pragma once


//线条绘制信息描述
struct sDrawLineInfo
{
	CPoint m_StartPoint;
	CPoint m_EndPoint;
};

class CDlgDrawTiaoXing : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrawTiaoXing)

public:
	CDlgDrawTiaoXing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDrawTiaoXing();

	enum { IDD = IDD_DRAW_TIAO_XING_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedFirstBtn();
	afx_msg void OnBnClickedCleanBtn();
	void UpdateBtnStatus();

public:

	//设置绘制数据
	void SetDrawData(vector<sDrawInfoList>& DrawAllInfo,CString Title,int TiaoXingCount);

private:

	//绘制条形
	void DrawTiaoXing(CDC* pDC,CRect Rect,int DataIndex);

	//绘制方框
	void DrawFrame(CDC* pDC,CRect TempRect,COLORREF Color,int FrameWidth=1);

	//初始化条形区域
	void InitRect();

	//获取条形区域
	vector<CRect> GetTiaoXingRect(CRect Rect);

	//通过位置获取文本
	CString GetTextByPoint(CPoint Point);

	//通过位置获取索引
	int GetIndexByPoint(CPoint Point);

	//创建内存设备环境
	void CreateMemDC();

	//绘制图形
	void Draw();

	


private:

	vector<sDrawInfoList>  m_DrawData;          //绘制数据
	int                    m_DrawIndex;         //绘制索引
	int                    m_TiaoXingHeight;    //条形单比例高度

	vector<CRect>          m_RectList;          //Rect 矩形区域列表
	vector<sDrawLineInfo>  m_DrawLineInfoList; //线条绘制信息
	sDrawLineInfo          m_CurrentDrawLine;  //当前线条

	CString                m_DrawText;     //绘制文本信息
	CPoint                 m_TextPoint;    //绘制文本位置
	int                    m_TiaoXingCount; //条形数

	bool                   m_IsDrawSingle;
	int                    m_SingleDrawIndex; //绘制单个索引
	CRect                  m_SingleRect;      //单个的矩形绘制区域


	CDC MemDC;
	CBitmap Bmp;
	
};
