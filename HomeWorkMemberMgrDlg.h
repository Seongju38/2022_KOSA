
// HomeWorkMemberMgrDlg.h: 헤더 파일
//

#pragma once

class CMember {
public:
	CMember() {
		TRACE("생성자\n");
	}
	~CMember() {
		TRACE("소멸자\n");
	}

	void find(int a, int b) {

	}

	CString m_strId;
	CString m_strName;
	int     m_nPostCode;
	CString m_strAddress;
	BOOL    m_bSex;
	CString m_strPhone1;
	CString m_strPhone2;
	CString m_strPhone3;
	int     m_nAge;
	int		m_nHobby;
};

using CMemberPtr = shared_ptr<CMember>;

// CHomeWorkMemberMgrDlg 대화 상자
class CHomeWorkMemberMgrDlg : public CDialog
{
	// 생성입니다.
public:
	CHomeWorkMemberMgrDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	vector<CMemberPtr> m_array;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMBERMGR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	CString m_strID;
	CString m_strName;
	BOOL m_bMale;
	BOOL m_bFemale;
	int m_nAge;
	CString m_strPhone1;
	CString m_strPhone2;
	CString m_strPhone3;
	int m_nPostCode;
	CString m_strAddress;
	int m_nHobby;

	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonCheck();
};
