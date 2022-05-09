
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
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CHWHospitalView::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CHWHospitalView::OnBnClickedButtonModify)
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

void CHWHospitalView::SetHospitalListView(int nRow, const CHospitalPtr pHospital)
{
	m_listView.SetItemText(nRow, 1, pHospital->strAuthDate);
	m_listView.SetItemText(nRow, 2, pHospital->strStatusName);
	m_listView.SetItemText(nRow, 3, pHospital->strStatusCode);
	m_listView.SetItemText(nRow, 4, pHospital->strDetaileStatusName);
	m_listView.SetItemText(nRow, 5, pHospital->strPhone);
	m_listView.SetItemText(nRow, 6, pHospital->strPostCode);
	m_listView.SetItemText(nRow, 7, pHospital->strAddress);
	m_listView.SetItemText(nRow, 8, pHospital->strRoadAddress);
	m_listView.SetItemText(nRow, 9, pHospital->strRoadPostCode);
	m_listView.SetItemText(nRow, 10, pHospital->strHospitalName);
	m_listView.SetItemText(nRow, 11, pHospital->strBusinessName);
	m_listView.SetItemText(nRow, 12, pHospital->strBusinessNickName);
	m_listView.SetItemText(nRow, 13, pHospital->strWorkerNum);
	m_listView.SetItemText(nRow, 14, pHospital->strRoomNum);
	m_listView.SetItemText(nRow, 15, pHospital->strBedNum);
	m_listView.SetItemText(nRow, 16, pHospital->strTreatmentSubject);
}

void CHWHospitalView::GetDBAllHospitalListView(vector<CHospitalPtr> HospitalList)
{
	//??????????????????????????????????????
	m_listView.DeleteAllItems();

	int nRow = 0;
	for (const auto& pHospital : HospitalList) {
		m_listView.InsertItem(nRow, pHospital->strHospitalNo, 0);
		SetHospitalListView(nRow, pHospital);
		nRow++;
	}
}

void CHWHospitalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//컬럼 정보 출력 
	m_listView.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 70);
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
	GetDBAllHospitalListView(hospitalDAO.GetListHospital());
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


/******************************기타구현**********************************/
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


void CHWHospitalView::OnBnClickedButtonDelete()
{
	const int nCount = m_listView.GetItemCount();
	CString strHospitalNo; // 삭제 할 HospitalNo 얻기
	CString strSQL;

	// 화면& DB에서 삭제
	CString strInParam;
	CArray<int, int> arr;

	// 삭제 위치와 삭제 병원 번호 얻기
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			// 삭제 할 병원 번호 얻기
			strHospitalNo = m_listView.GetItemText(i, 0);

			strInParam += strHospitalNo + _T(",");

			// 삭제 할 병원 번호의 위치를 배열에 추가
			arr.Add(i);
		}
	}

	try {
		if (strInParam.IsEmpty()) {
			AfxMessageBox(_T("삭제할 병원을 선택해 주세요"));
			return;
		}

		if (!strInParam.IsEmpty()) {
			// 맨 뒤에 있는 (,) 삭제
			strInParam.Delete(strInParam.GetLength() - 1, 1);

			AfxMessageBox(strInParam + _T("을 삭제하시겠습니까?"));

			// SQL 삭제 구문 생성
			strSQL = _T("DELETE FROM 병원 WHERE 번호 IN (") + strInParam + _T(")");

			m_db.BeginTrans();
			m_db.ExecuteSQL(strSQL);
			m_db.CommitTrans();

			// 화면에서 삭제 항목을 제거 - 예외가 발생되면 실행 안 함
			for (int i = 0; i < arr.GetSize(); i++) {
				m_listView.DeleteItem(arr.GetAt(i));
			}
		}
	}
	catch (const CException* p) {
		m_db.Rollback();

		TCHAR szErr[100];
		p->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
	}
}


void CHWHospitalView::OnBnClickedButtonModify()
{
	const int nCount = m_listView.GetItemCount();
	CString strHospitalNo;

	// 수정하기 위해 선택된 병원 번호 얻기
	int nRow;
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			strHospitalNo = m_listView.GetItemText(i, 0);
			nRow = i;
			break;
		}
	}

	if (strHospitalNo.IsEmpty()) {
		AfxMessageBox(_T("수정할 병원을 선택해 주세요."));
		return;
	}


	CHospitalDAO HDAO(m_db);

	vector<CHospitalPtr> HList = HDAO.GetListHospital();

	// 병원 번호로 병원 상세 정보 얻기
	CHospitalPtr pHospitalData = HDAO.GetDetailHospital(strHospitalNo);


	CMedicalSubjectDAO medicalSubjectDAO(m_db);
	map<CString, CString> mapMedicalSubject = medicalSubjectDAO.GetMapMedicalSubject();


	// 병원진료과목목록 전체 삭제 
	CMediSubListDAO mediSubListDAO(m_db);
	mediSubListDAO.DeleteAllMediSubList();
	CMediSubListPtr pMediSubList = make_shared<CMediSubList>();

	int nPos = 0;
	for (const auto& pHospital : HList) {
		// 병원진료과목목록 문자열 포인터 얻기
		LPTSTR lpszMediSubject = pHospital->strTreatmentSubject.GetBuffer();
		LPTSTR lpszToken = NULL;
		LPTSTR lpszNextToken = NULL;

		lpszToken = _tcstok_s(lpszMediSubject, _T(",· "), &lpszNextToken);
		while (lpszToken) {
			//m_listView.InsertItem(nPos, pHospital->strHospitalNo.GetBuffer(), 0);
			// , . 으로 분리한 문자열 출력 
			//m_listView.SetItemText(nPos, 16, lpszToken);

			// 병원진료과목에 대한 코드 찾기
			// 찾은 코드와 병원 번호를 이용하여 DB(병원진료과목목록 테이블)에 추가 
			pMediSubList->strHospitalNo = pHospital->strHospitalNo;
			pMediSubList->strTreatCode = mapMedicalSubject[lpszToken];
			if (!pMediSubList->strTreatCode.IsEmpty()) {
				mediSubListDAO.InsertMediSubList(pMediSubList);
			}

			nPos++;
			lpszToken = _tcstok_s(NULL, _T(",· "), &lpszNextToken);
		}
	}

	// 대화상자에 병원 데이터 전달 및 출력
	//CHospitalDialog dlg;
	CHospitalDialog dlg(HList, pHospitalData);

	if (dlg.DoModal() == IDOK) {
		pHospitalData->strHospitalNo = dlg.m_strHospitalName;

	}
}
