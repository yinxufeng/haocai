#pragma once


// CRedBallDlg 对话框

class CRedBallDlg : public CDialog
{
	DECLARE_DYNAMIC(CRedBallDlg)

public:
	CRedBallDlg(CWnd* pParent = NULL); 
	virtual ~CRedBallDlg();

	enum eDrawType{DRAW_RED_BALL_1,DRAW_RED_BALL_2,DRAW_RED_BALL_3,DRAW_RED_BALL_4,DRAW_RED_BALL_5,DRAW_RED_BALL_6,DRAW_RED_BALL_ALL};
// 对话框数据
	enum { IDD = IDD_RED_BALL_DLG };

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();


	void SetDataList(vector<sShuangSeQiu>& DataList){ m_DrawIndex=0;m_DataList=DataList;}


	void DrawZuoBiao(CDC* pDC,CRect& Rect);

	void DrawHongQiu(CDC* pDC,eDrawType Type,CRect Rect);

	void DrawPoint(CDC* pDC,eDrawType Type,CRect Rect,int DrawIndex=0);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()


private:
	eDrawType m_DrawType;
	vector<sShuangSeQiu> m_DataList;
	int                  m_DrawIndex;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
