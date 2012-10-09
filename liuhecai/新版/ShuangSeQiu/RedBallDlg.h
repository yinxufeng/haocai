#pragma once


// CRedBallDlg 对话框

class CRedBallDlg : public CDialog
{
	DECLARE_DYNAMIC(CRedBallDlg)

public:
	CRedBallDlg(CWnd* pParent = NULL); 
	virtual ~CRedBallDlg();
// 对话框数据
	enum { IDD = IDD_RED_BALL_DLG };

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void SetDataList(vector<sShuangSeQiu>& DataList){ m_DataList = DataList; m_DrawIndex=m_DataList.size()-1;if(m_DrawIndex< 0)m_DrawIndex=0;}

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DrawData(CDC* pDC,CRect Rect,int Data,vector<int>&DataList);
	void DrawData2(CDC* pDC,CRect Rect,int Data,vector<int>&DataList);

	void DrawFrame(CDC* pDC,CRect Rect,COLORREF Color,int FrameWidth=1);

	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedFirstBtn();
	
	void UpdateBtnStatus();

	CPoint GetCenterPoint(CRect Rect);
	CRect MapCenterPoint(CPoint Point,CRect Rect);

	//获取抛物线参数
	void GetPaoWuXianCanShu(CPoint Point1,CPoint Point2,CPoint Point3,float& A,float& B,float& C);

	//获取数据位置
	CPoint GetPointByData(int Data);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()


private:

	int                  m_DrawIndex;
	vector<sShuangSeQiu> m_DataList;

};
