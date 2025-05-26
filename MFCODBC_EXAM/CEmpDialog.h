#pragma once


// CEmpDialog 대화 상자

class CEmpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEmpDialog)

public:
	CEmpDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEmpDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEmpNo;
	CString m_strEname;
	CString m_strJob;
	CComboBox m_comboMgr;
	CString m_strMgrName;
	COleDateTime m_hiredate;
	int m_nSal;
	int m_nComm;
	CComboBox m_comboDept;
	CString m_strDName;
};
