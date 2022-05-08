
// HWHospitalView.cpp: CHWHospitalView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HWHospital.h"
#endif

#include "HWHospitalDoc.h"
#include "HWHospitalView.h"

#include "CHospital.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHWHospitalView

IMPLEMENT_DYNCREATE(CHWHospitalView, CFormView)

BEGIN_MESSAGE_MAP(CHWHospitalView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CHWHospitalView 생성/소멸

CHWHospitalView::CHWHospitalView() noexcept
	: CFormView(IDD_HWHOSPITAL_FORM)
{
	// DB 연결
	BOOL bRet = m_db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (!bRet) {
		AfxMessageBox(_T("DB 연결 실패"));
	}
}

CHWHospitalView::~CHWHospitalView()
{
	if (m_db.IsOpen()) {
		// DB 연결 종료
		m_db.Close();
	}
}

void CHWHospitalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listView);
}

BOOL CHWHospitalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CHWHospitalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//컬럼 정보 출력 
	m_listView.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 50);
	m_listView.InsertColumn(1, _T("인허가일자"), LVCFMT_LEFT , 80);
	m_listView.InsertColumn(2, _T("영업상태명"), LVCFMT_LEFT, 80);
	m_listView.InsertColumn(3, _T("상세영업상태코드"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(4, _T("상세영업상태명"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(5, _T("소재지전화"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(6, _T("소재지우편번호"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(7, _T("소재지전체주소"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(8, _T("도로명전체주소"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(9, _T("도로명우편번호"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(10, _T("사업장명"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(11, _T("업태구분명"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(12, _T("의료기관종별명"), LVCFMT_LEFT, 120);
	m_listView.InsertColumn(13, _T("의료인수"), LVCFMT_LEFT, 80);
	m_listView.InsertColumn(14, _T("입원실수"), LVCFMT_LEFT, 80);
	m_listView.InsertColumn(15, _T("병상수"), LVCFMT_LEFT, 80);
	m_listView.InsertColumn(16, _T("진료과목내용명"), LVCFMT_LEFT, 250);

	// 체크박스
	DWORD dwExStyle = m_listView.GetExtendedStyle();
	m_listView.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 병원 전체 데이터 읽기
	CHospitalDAO hospitalDAO(m_db);
	vector<CHospitalPtr> list = hospitalDAO.GetListHospital();
	int nPos = 0;
	for (const auto& pHospital : list) {
		m_listView.InsertItem(nPos, pHospital->strHospitalNo.GetBuffer(), 0);
		m_listView.SetItemText(nPos, 1, pHospital->strAuthDate.GetBuffer());
		m_listView.SetItemText(nPos, 2, pHospital->strStatusName.GetBuffer());
		m_listView.SetItemText(nPos, 3, pHospital->strStatusCode.GetBuffer());
		m_listView.SetItemText(nPos, 4, pHospital->strDetaileStatusName.GetBuffer());
		m_listView.SetItemText(nPos, 5, pHospital->strPhone.GetBuffer());
		m_listView.SetItemText(nPos, 6, pHospital->strPostCode.GetBuffer());
		m_listView.SetItemText(nPos, 7, pHospital->strAddress.GetBuffer());
		m_listView.SetItemText(nPos, 8, pHospital->strRoadAddress.GetBuffer());
		m_listView.SetItemText(nPos, 9, pHospital->strRoadPostCode.GetBuffer());
		m_listView.SetItemText(nPos, 10, pHospital->strHospitalName.GetBuffer());
		m_listView.SetItemText(nPos, 11, pHospital->strBusinessName.GetBuffer());
		m_listView.SetItemText(nPos, 12, pHospital->strBusinessNickName.GetBuffer());
		m_listView.SetItemText(nPos, 13, pHospital->strWorkerNum.GetBuffer());
		m_listView.SetItemText(nPos, 14, pHospital->strRoomNum.GetBuffer());
		m_listView.SetItemText(nPos, 15, pHospital->strBedNum.GetBuffer());
		m_listView.SetItemText(nPos, 16, pHospital->strTreatmentSubject.GetBuffer());
		nPos++;
	}

}


// CHWHospitalView 인쇄

BOOL CHWHospitalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHWHospitalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHWHospitalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CHWHospitalView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CHWHospitalView 진단

#ifdef _DEBUG
void CHWHospitalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHWHospitalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHWHospitalDoc* CHWHospitalView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHWHospitalDoc)));
	return (CHWHospitalDoc*)m_pDocument;
}
#endif //_DEBUG


// CHWHospitalView 메시지 처리기


void CHWHospitalView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// 창이 resize될 때 안에 있는 요소들도 같이 resize 되도록 함
	CWnd* pButton = GetDlgItem(IDC_BUTTON_ADD);
	if (pButton) {
		pButton->MoveWindow(cx - 420, 20, 100, 40);
	}
	pButton = GetDlgItem(IDC_BUTTON_MODIFY);
	if (pButton) {
		pButton->MoveWindow(cx - 320, 20, 100, 40);
	}
	pButton = GetDlgItem(IDC_BUTTON_DELETE);
	if (pButton) {
		pButton->MoveWindow(cx - 220, 20, 100, 40);
	}
	pButton = GetDlgItem(IDC_BUTTON_SEARCH);
	if (pButton) {
		pButton->MoveWindow(cx - 120, 20, 100, 40);
	}
	if (m_listView.GetSafeHwnd()) {
		m_listView.MoveWindow(0, 80, cx, cy - 80);
	}
}
