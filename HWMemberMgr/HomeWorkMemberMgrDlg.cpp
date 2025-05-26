
// HomeWorkMemberMgrDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HomeWorkMemberMgr.h"
#include "HomeWorkMemberMgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMemberMgrDlg 대화 상자



CHomeWorkMemberMgrDlg::CHomeWorkMemberMgrDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MEMBERMGR_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strName(_T(""))
	, m_bMale(FALSE)
	, m_bFemale(FALSE)
	, m_strPhone1(_T(""))
	, m_strPhone2(_T(""))
	, m_strPhone3(_T(""))
	, m_strAddress(_T(""))
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
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CHomeWorkMemberMgrDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CHomeWorkMemberMgrDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CHomeWorkMemberMgrDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CHomeWorkMemberMgrDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CHomeWorkMemberMgrDlg::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CHomeWorkMemberMgrDlg 메시지 처리기

BOOL CHomeWorkMemberMgrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHomeWorkMemberMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
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



void CHomeWorkMemberMgrDlg::OnBnClickedButtonNew()
{
	m_strID = _T("");
	m_strName = _T("");
	m_nPostCode = 0;
	m_strAddress = _T("");
	m_bMale = FALSE;
	m_bFemale = FALSE;
	m_strPhone1 = _T("");
	m_strPhone2 = _T("");
	m_strPhone3 = _T("");
	m_nAge = 0;
	m_nHobby = 0;

	UpdateData(FALSE);

}


void CHomeWorkMemberMgrDlg::OnBnClickedButtonAdd()
{
	if (!UpdateData()) return;

	CMemberPtr pMember = make_shared<CMember>();

	pMember->m_strId = m_strID;
	pMember->m_strName = m_strName;
	pMember->m_nPostCode = m_nPostCode;
	pMember->m_strAddress = m_strAddress;
	pMember->m_bSex = m_bMale ? TRUE : FALSE;
	pMember->m_strPhone1 = m_strPhone1;
	pMember->m_strPhone2 = m_strPhone2;
	pMember->m_strPhone3 = m_strPhone3;
	pMember->m_nAge = m_nAge;
	pMember->m_nHobby = m_nHobby;

	m_array.push_back(pMember);

	AfxMessageBox(_T("고객 정보가 등록되었습니다."));

	OnBnClickedButtonNew();
}


void CHomeWorkMemberMgrDlg::OnBnClickedButtonModify()
{
	if (!UpdateData()) return;

	CString& strId = m_strID;
	auto& it = find_if(m_array.cbegin(), m_array.cend(), [strId](auto& pMember) -> int{return pMember->m_strId == strId;});

	if (it != m_array.cend()) {
		CMemberPtr pMember = *it;

		pMember->m_strId = m_strID;
		pMember->m_strName = m_strName;
		pMember->m_nPostCode = m_nPostCode;
		pMember->m_strAddress = m_strAddress;
		pMember->m_bSex = m_bMale ? TRUE : FALSE;
		pMember->m_strPhone1 = m_strPhone1;
		pMember->m_strPhone2 = m_strPhone2;
		pMember->m_strPhone3 = m_strPhone3;
		pMember->m_nAge = m_nAge;
		pMember->m_nHobby = m_nHobby;

		AfxMessageBox(_T("고객 정보가 수정되었습니다."));
	}
	else {
		AfxMessageBox(_T("찾는 아이디의 정보가 존재하지 않습니다."));
	}

}


void CHomeWorkMemberMgrDlg::OnBnClickedButtonDelete()
{
	CString& strId = m_strID;
	const auto& it = find_if(m_array.cbegin(), m_array.cend(), [strId](auto& pMember) -> int {return pMember->m_strId == strId; });

	if (it != m_array.cend()) {
		m_array.erase(it);
		AfxMessageBox(_T("자료를 찾아서 삭제했습니다."));
	}
	else {
		AfxMessageBox(_T("찾는 아이디의 정보가 존재하지 않습니다."));
	}
}


void CHomeWorkMemberMgrDlg::OnBnClickedButtonCheck()
{
	CString& strId = m_strID;
	const auto& it = find_if(m_array.cbegin(), m_array.cend(), [strId](auto& pMember) -> int {return pMember->m_strId == strId; });

	if (it != m_array.cend()) {
		CMemberPtr pMember = *it;

		m_strID = pMember->m_strId;
		m_strName = pMember->m_strName;
		m_nPostCode = pMember->m_nPostCode;
		m_strAddress = pMember->m_strAddress;
		m_bMale = pMember->m_bSex;
		m_bFemale = pMember->m_bSex == FALSE;
		m_strPhone1 = pMember->m_strPhone1;
		m_strPhone2 = pMember->m_strPhone2;
		m_strPhone3 = pMember->m_strPhone3;
		m_nAge = pMember->m_nAge;
		m_nHobby = pMember->m_nHobby;

		UpdateData(FALSE);

		return;
	}
	else {
		AfxMessageBox(_T("찾는 아이디의 정보가 존재하지 않습니다."));
	}

}
