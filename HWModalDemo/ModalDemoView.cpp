
// ModalDemoView.cpp: CModalDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ModalDemo.h"
#endif

#include "ModalDemoDoc.h"
#include "ModalDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModalDemoView

IMPLEMENT_DYNCREATE(CModalDemoView, CFormView)

BEGIN_MESSAGE_MAP(CModalDemoView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CModalDemoView::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON2, &CModalDemoView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CModalDemoView::OnBnClickedButton3)
	ON_LBN_SELCHANGE(IDC_LIST1, &CModalDemoView::OnLbnSelchangeList1)
END_MESSAGE_MAP()

// CModalDemoView 생성/소멸

CModalDemoView::CModalDemoView() noexcept
	: CFormView(IDD_MODALDEMO_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CModalDemoView::~CModalDemoView()
{
}

void CModalDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

BOOL CModalDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CModalDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CModalDemoView 인쇄

BOOL CModalDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CModalDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CModalDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CModalDemoView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CModalDemoView 진단

#ifdef _DEBUG
void CModalDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CModalDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CModalDemoDoc* CModalDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModalDemoDoc)));
	return (CModalDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CModalDemoView 메시지 처리기

#include "CUserDlg.h"
#include "HomeWorkMemberMgrDlg.h"

void CModalDemoView::OnBnClickedButtonInsert()
{
	CHomeWorkMemberMgrDlg dlg(GetDocument()->m_memberMgr);
	
	if (dlg.DoModal() == IDOK) {
		CMemberPtr pMember = dlg.GetMemberPtr();
		GetDocument()->InsertMember(pMember);

		m_listBox.AddString(pMember->m_strId.GetBuffer());
	}
}

void CModalDemoView::OnBnClickedButton2()
{

	CHomeWorkMemberMgrDlg dlg(GetDocument()->m_memberMgr);

	int nCurSel = m_listBox.GetCurSel();

	if (nCurSel < 0) return;

	CString strId;
	m_listBox.GetText(nCurSel, strId);

	CMemberPtr pMember = GetDocument()->GetMember(strId);
	if (pMember == nullptr) return;

	dlg.SetMemberPtr(pMember);

	if (dlg.DoModal() == IDOK) {

		*pMember = dlg.GetMemberPtr();
	}

}


void CModalDemoView::OnBnClickedButton3()
{
	if (AfxMessageBox(_T("삭제하시겠습니까?"), MB_YESNO) != IDYES) {
		return;
	}

	int nCurSel = m_listBox.GetCurSel();

	if (nCurSel < 0) return;

	CString strId;
	m_listBox.GetText(nCurSel, strId);

	GetDocument()->DeleteMember(strId);

	m_listBox.DeleteString(nCurSel);

	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
}


void CModalDemoView::OnLbnSelchangeList1()
{
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
}
