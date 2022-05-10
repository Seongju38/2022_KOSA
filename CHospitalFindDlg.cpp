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
END_MESSAGE_MAP()


// CHospitalFindDlg 메시지 처리기
