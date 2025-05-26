// CUserDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ModalDemo.h"
#include "CUserDlg.h"
#include "afxdialogex.h"


// CUserDlg 대화 상자

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strName(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
END_MESSAGE_MAP()


// CUserDlg 메시지 처리기


BOOL CUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetSafeHwnd();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
