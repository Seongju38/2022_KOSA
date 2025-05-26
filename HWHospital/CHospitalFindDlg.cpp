// CHospitalFindDlg.cpp: 구현 파일
//

#include "pch.h"
#include "HWHospital.h"
#include "CHospitalFindDlg.h"
#include "afxdialogex.h"


// CHospitalFindDlg 대화 상자

IMPLEMENT_DYNAMIC(CHospitalFindDlg, CDialogEx)

CHospitalFindDlg::CHospitalFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_FIND, pParent)
	, m_strHospitalName(_T(""))
	, m_strHospitalPhone(_T(""))
{

}

CHospitalFindDlg::~CHospitalFindDlg()
{
}

void CHospitalFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strHospitalName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strHospitalPhone);
}


BEGIN_MESSAGE_MAP(CHospitalFindDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CHospitalFindDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_PHONE, &CHospitalFindDlg::OnEnChangeEditPhone)
END_MESSAGE_MAP()


// CHospitalFindDlg 메시지 처리기



void CHospitalFindDlg::OnEnChangeEditName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	CheckStr();
}


void CHospitalFindDlg::OnEnChangeEditPhone()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	CheckStr();
}

void CHospitalFindDlg::CheckStr()
{
	CString strHName;
	CString strHPhone;

	// Edit Control에서 입력된 문자열 얻기
	GetDlgItemText(IDC_EDIT_NAME, strHName);
	GetDlgItemText(IDC_EDIT_PHONE, strHPhone);

	if (strHName.IsEmpty() && strHPhone.IsEmpty())
		GetDlgItem(IDOK)->EnableWindow(FALSE); // 버튼 비활성화
}
