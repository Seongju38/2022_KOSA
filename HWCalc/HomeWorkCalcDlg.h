
// HomeWorkCalcDlg.h: 헤더 파일
//

#pragma once


// CHomeWorkCalcDlg 대화 상자
class CHomeWorkCalcDlg : public CDialog
{
// 생성입니다.
public:
	CHomeWorkCalcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOMEWORKCALC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	void AddNumber(LPCTSTR lpszNumber);


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_value;
	int		m_op;
	CString m_op1;
	CString m_op2;
	CEdit m_ctlEdit;

	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonSum();
	afx_msg void OnBnClickedButtonMult();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonResult();
	afx_msg void OnBnClickedButtonC();

};
