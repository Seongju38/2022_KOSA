
// HomeWorkCalcDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HomeWorkCalc.h"
#include "HomeWorkCalcDlg.h"
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


// CHomeWorkCalcDlg 대화 상자



CHomeWorkCalcDlg::CHomeWorkCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HOMEWORKCALC_DIALOG, pParent)
	, m_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHomeWorkCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_Control(pDX, IDC_VALUE, m_ctlEdit);
}

BEGIN_MESSAGE_MAP(CHomeWorkCalcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON0, &CHomeWorkCalcDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON1, &CHomeWorkCalcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHomeWorkCalcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHomeWorkCalcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHomeWorkCalcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHomeWorkCalcDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CHomeWorkCalcDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CHomeWorkCalcDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CHomeWorkCalcDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CHomeWorkCalcDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_SUM, &CHomeWorkCalcDlg::OnBnClickedButtonSum)
	ON_BN_CLICKED(IDC_BUTTON_MULT, &CHomeWorkCalcDlg::OnBnClickedButtonMult)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CHomeWorkCalcDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CHomeWorkCalcDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CHomeWorkCalcDlg::OnBnClickedButtonResult)
	ON_BN_CLICKED(IDC_BUTTON_C, &CHomeWorkCalcDlg::OnBnClickedButtonC)
END_MESSAGE_MAP()


// CHomeWorkCalcDlg 메시지 처리기

BOOL CHomeWorkCalcDlg::OnInitDialog()
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

void CHomeWorkCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHomeWorkCalcDlg::OnPaint()
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
HCURSOR CHomeWorkCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHomeWorkCalcDlg::AddNumber(LPCTSTR lpszNumber) {
	UpdateData();
	if (m_value == _T("값을 입력해주세요.")) {
		m_value = _T("");
	}
	m_value += lpszNumber;
	UpdateData(FALSE);
}

void CHomeWorkCalcDlg::OnBnClickedButton0()
{
	AddNumber(_T("0"));
}

void CHomeWorkCalcDlg::OnBnClickedButton1()
{
	AddNumber(_T("1"));
}


void CHomeWorkCalcDlg::OnBnClickedButton2()
{
	AddNumber(_T("2"));
}


void CHomeWorkCalcDlg::OnBnClickedButton3()
{
	AddNumber(_T("3"));
}


void CHomeWorkCalcDlg::OnBnClickedButton4()
{
	AddNumber(_T("4"));
}


void CHomeWorkCalcDlg::OnBnClickedButton5()
{
	AddNumber(_T("5"));
}


void CHomeWorkCalcDlg::OnBnClickedButton6()
{
	AddNumber(_T("6"));
}


void CHomeWorkCalcDlg::OnBnClickedButton7()
{
	AddNumber(_T("7"));
}


void CHomeWorkCalcDlg::OnBnClickedButton8()
{
	AddNumber(_T("8"));
}


void CHomeWorkCalcDlg::OnBnClickedButton9()
{
	AddNumber(_T("9"));
}


void CHomeWorkCalcDlg::OnBnClickedButtonSum()
{
	UpdateData();
	m_op1 = m_value;
	m_op = 1;
	m_value = _T("");
	UpdateData(FALSE);
}

void CHomeWorkCalcDlg::OnBnClickedButtonSub()
{
	UpdateData();
	m_op1 = m_value;
	m_op = 2;
	m_value = _T("");
	UpdateData(FALSE);
}

void CHomeWorkCalcDlg::OnBnClickedButtonMult()
{
	UpdateData();
	m_op1 = m_value;
	m_op = 3;
	m_value = _T("");
	UpdateData(FALSE);
}


void CHomeWorkCalcDlg::OnBnClickedButtonDiv()
{
	UpdateData();
	m_op1 = m_value;
	m_op = 4;
	m_value = _T("");
	UpdateData(FALSE);
}


void CHomeWorkCalcDlg::OnBnClickedButtonResult()
{

	UpdateData();
	m_op2 = m_value;
	int result = 0;
	switch (m_op) {
	case 1:
		result = _ttoi(m_op1.GetBuffer()) + _ttoi(m_op2.GetBuffer());
		break;
	case 2:
		result = _ttoi(m_op1.GetBuffer()) - _ttoi(m_op2.GetBuffer());
		break;
	case 3:
		result = _ttoi(m_op1.GetBuffer()) * _ttoi(m_op2.GetBuffer());
		break;
	case 4:
		if (_ttoi(m_op2.GetBuffer()) == 0)
			result = -9999;
		else
			result = _ttoi(m_op1.GetBuffer()) / _ttoi(m_op2.GetBuffer());
		break;
	}

	if (result == -9999)
		m_value = _T("오류");
	else
		m_value.Format(_T("%d"), result);

	UpdateData(FALSE);

}


void CHomeWorkCalcDlg::OnBnClickedButtonC()
{
	m_ctlEdit.SetSel(0, -1, TRUE);
	m_ctlEdit.Clear();
}
