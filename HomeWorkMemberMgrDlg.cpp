
// HomeWorkMemberMgrDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HomeWorkMemberMgrDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "MainFrm.h"
#include "ModalDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHomeWorkMemberMgrDlg 대화 상자

CHomeWorkMemberMgrDlg::CHomeWorkMemberMgrDlg(CMemberMgr& pMemberMgr, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MEMBERMGR_DIALOG, pParent), m_pMemberMgr(pMemberMgr)
	, m_strID(_T(""))
	, m_strName(_T(""))
	, m_bMale(FALSE)
	, m_bFemale(FALSE)
	, m_strPhone1(_T(""))
	, m_strPhone2(_T(""))
	, m_strPhone3(_T(""))
	, m_strAddress(_T(""))
	, m_nPostCode(0)
	, m_nAge(0)
	, m_nHobby(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHomeWorkMemberMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Check(pDX, IDC_CHECK_MEN, m_bMale);
	DDX_Check(pDX, IDC_CHECK_WOMEN, m_bFemale);
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDX_Text(pDX, IDC_EDIT_PHONE1, m_strPhone1);
	DDX_Text(pDX, IDC_EDIT_PHONE2, m_strPhone2);
	DDX_Text(pDX, IDC_EDIT_PHONE3, m_strPhone3);
	DDX_Text(pDX, IDC_EDIT_POSTNUM, m_nPostCode);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
}

BEGIN_MESSAGE_MAP(CHomeWorkMemberMgrDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHomeWorkMemberMgrDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHomeWorkMemberMgrDlg 메시지 처리기

BOOL CHomeWorkMemberMgrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_EDIT_ID)->EnableWindow(m_strID.IsEmpty());

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHomeWorkMemberMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHomeWorkMemberMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHomeWorkMemberMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHomeWorkMemberMgrDlg::OnBnClickedOk()
{
	if (UpdateData() == FALSE) {
		return;
	}

	//공백 제거
	m_strID = m_strID.Trim();
	m_strName = m_strName.Trim();
	m_strAddress = m_strAddress.Trim();
	m_strPhone1 = m_strPhone1.Trim();
	m_strPhone2 = m_strPhone2.Trim();
	m_strPhone3 = m_strPhone3.Trim();

	//값입력 여부 확인
	if (IsEmpty(m_strID, _T("아이디를 입력해주세요"), IDC_EDIT_ID)) return;
	if (IsEmpty(m_strName, _T("이름을 입력해주세요"), IDC_EDIT_NAME)) return;
	if (IsEmpty(m_strAddress, _T("주소를 입력해주세요"), IDC_EDIT_ADDRESS)) return;
	if (IsEmpty(m_strPhone1, _T("전화번호를 입력해주세요"), IDC_EDIT_PHONE1)) return;
	if (IsEmpty(m_strPhone2, _T("전화번호를 입력해주세요"), IDC_EDIT_PHONE2)) return;
	if (IsEmpty(m_strPhone3, _T("전화번호를 입력해주세요"), IDC_EDIT_PHONE3)) return;

	//중복여부 확인 
	CWnd* pWndId = GetDlgItem(IDC_EDIT_ID);
	if (pWndId != nullptr && pWndId->IsWindowEnabled()) {
		CMemberPtr pMember = m_pMemberMgr.GetMember(m_strID);
		if (pMember != nullptr && !pMember->m_strId.IsEmpty()) {
			AfxMessageBox(_T("아이디가 중복 되었습니다"));
			return;
		}
	}

	CDialog::OnOK();
}

bool CHomeWorkMemberMgrDlg::IsEmpty(const CString& strText, LPCTSTR lpszMsg, UINT id) const {
	if (strText.GetLength() == 0) {
		AfxMessageBox(lpszMsg);
		GetDlgItem(id)->SetFocus();
		return true;
	}
	return false;
}
