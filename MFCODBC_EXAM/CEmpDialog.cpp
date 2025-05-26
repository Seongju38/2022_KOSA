// CEmpDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCODBC_EXAM.h"
#include "CEmpDialog.h"
#include "afxdialogex.h"


// CEmpDialog 대화 상자

IMPLEMENT_DYNAMIC(CEmpDialog, CDialogEx)

CEmpDialog::CEmpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EMPDIALOG, pParent)
	, m_strEmpNo(_T(""))
	, m_strEname(_T(""))
	, m_strJob(_T(""))
	, m_strMgrName(_T(""))
	, m_hiredate(COleDateTime::GetCurrentTime())
	, m_nSal(0)
	, m_nComm(0)
	, m_strDName(_T(""))
{

}

CEmpDialog::~CEmpDialog()
{
}

void CEmpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strEmpNo);
	DDX_Text(pDX, IDC_EDIT2, m_strEname);
	DDX_Text(pDX, IDC_EDIT3, m_strJob);
	DDX_Control(pDX, IDC_COMBO1, m_comboMgr);
	DDX_CBString(pDX, IDC_COMBO1, m_strMgrName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_hiredate);
	DDX_Text(pDX, IDC_EDIT4, m_nSal);
	DDX_Text(pDX, IDC_EDIT5, m_nComm);
	DDX_Control(pDX, IDC_COMBO2, m_comboDept);
	DDX_CBString(pDX, IDC_COMBO2, m_strDName);
}


BEGIN_MESSAGE_MAP(CEmpDialog, CDialogEx)
END_MESSAGE_MAP()


// CEmpDialog 메시지 처리기
