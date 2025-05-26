
// MFCODBC_EXAMView.cpp: CMFCODBCEXAMView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCODBC_EXAM.h"
#endif

#include "MFCODBC_EXAMDoc.h"
#include "MFCODBC_EXAMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*************************************************************코드추가*************************************************************/
#include "CEmpDialog.h"

#include <memory> // 스마트 포인터 사용을 위함
#include <vector>

using namespace std;

class CEmp {
public:
	CString strEmpNo;
	CString strEName;
	CString strJob;
	CString strMgr; // 매니저 사원번호
	CString strMgrName; // 매니저 이름
	CString strHireDate;
	CString strSal;
	CString strComm;
	CString strDeptNo; // 부서번호
	CString strDName; // 부서이름
};
using CEmpPtr = shared_ptr<CEmp>;

class CDept {
public:
	CString strDeptNo;
	CString strDName;
	CString strLoc;
};
using CDeptPtr = shared_ptr<CDept>;

vector<CEmpPtr> GetListEmp(CDatabase& db)
{
	vector<CEmpPtr> resultList;

	CRecordset  rs(&db);
	rs.Open(CRecordset::forwardOnly,
		_T("SELECT a.empno, a.ename, a.job, a.mgr, b.ename mgr_name, \
				to_char(a.hiredate, 'YYYY-MM-DD'), to_char(a.sal, '99,999'), a.comm, a.deptno, c.dname \
			FROM emp a, emp b, dept c \
			WHERE a.mgr = b.empno(+) \
			AND a.deptno = c.deptno(+)"));

	// rs를 하나의 파일로 봄
	while (!rs.IsEOF()) {
		// 스마트 포인터를 이용하여 객체 생성함
		CEmpPtr pEmp = make_shared<CEmp>( );
		if (pEmp == nullptr) return vector<CEmpPtr>( ); // 포인터 사용 시 반드시 nullptr 확인

		rs.GetFieldValue((short)0, pEmp->strEmpNo);
		rs.GetFieldValue(1, pEmp->strEName);
		rs.GetFieldValue(2, pEmp->strJob);
		rs.GetFieldValue(3, pEmp->strMgr);
		rs.GetFieldValue(4, pEmp->strMgrName);
		rs.GetFieldValue(5, pEmp->strHireDate);
		rs.GetFieldValue(6, pEmp->strSal);
		rs.GetFieldValue(7, pEmp->strComm);
		rs.GetFieldValue(8, pEmp->strDeptNo);
		rs.GetFieldValue(9, pEmp->strDName);

		rs.MoveNext();

		// 배열에 스마트 포인터 객체를 추가한다.
		resultList.push_back(pEmp);
	}
	rs.Close();

	return resultList;
}

CEmpPtr GetEmp(CDatabase& db, CString strEmpNo)
{
	CEmpPtr pEmp = make_shared<CEmp>( );

	CRecordset  rs(&db);
	rs.Open(CRecordset::forwardOnly,
		_T("SELECT a.empno, a.ename, a.job, a.mgr, b.ename mgr_name, \
				to_char(a.hiredate, 'YYYY-MM-DD'), to_char(a.sal, '99,999'), a.comm, a.deptno, c.dname \
			FROM emp a, emp b, dept c \
			WHERE a.mgr = b.empno(+) \
			AND a.deptno = c.deptno(+) \
			AND a.empno = ") + strEmpNo);

	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, pEmp->strEmpNo);
		rs.GetFieldValue(1, pEmp->strEName);
		rs.GetFieldValue(2, pEmp->strJob);
		rs.GetFieldValue(3, pEmp->strMgr);
		rs.GetFieldValue(4, pEmp->strMgrName);
		rs.GetFieldValue(5, pEmp->strHireDate);
		rs.GetFieldValue(6, pEmp->strSal);
		rs.GetFieldValue(7, pEmp->strComm);
		rs.GetFieldValue(8, pEmp->strDeptNo);
		rs.GetFieldValue(9, pEmp->strDName);
	}
	rs.Close();

	return pEmp;
}

vector<CDeptPtr> GetListDept(CDatabase& db)
{
	vector<CDeptPtr> resultList;

	// 2. SQL 구문 실행
	CRecordset  rs(&db);
	rs.Open(CRecordset::forwardOnly,
		_T("SELECT * FROM dept"));

	// rs를 하나의 파일로 봄
	while (!rs.IsEOF()) {
		CDeptPtr pDept = make_shared<CDept>();
		if (pDept == nullptr) return vector<CDeptPtr>();

		rs.GetFieldValue((short)0, pDept->strDeptNo);
		rs.GetFieldValue(1, pDept->strDName);
		rs.GetFieldValue(2, pDept->strLoc);

		rs.MoveNext();

		// 배열에 스마트 포인터 객체를 추가한다.
		resultList.push_back(pDept);
	}
	rs.Close();

	return resultList;
}

/************************************************************************************************************************************/

// CMFCODBCEXAMView

IMPLEMENT_DYNCREATE(CMFCODBCEXAMView, CFormView)

BEGIN_MESSAGE_MAP(CMFCODBCEXAMView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCODBCEXAMView::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMFCODBCEXAMView::OnBnClickedButtonModify)
END_MESSAGE_MAP()

// CMFCODBCEXAMView 생성/소멸

CMFCODBCEXAMView::CMFCODBCEXAMView() noexcept
	: CFormView(IDD_MFCODBC_EXAM_FORM)
{
	/*************************************************************코드추가*************************************************************/
	BOOL bRet = m_db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (!bRet) {
		AfxMessageBox(_T("DB 연결 실패"));
	}
}

CMFCODBCEXAMView::~CMFCODBCEXAMView()
{
	if (m_db.IsOpen()) {
		// DB 연결 종료
		m_db.Close();
	}
}

void CMFCODBCEXAMView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listView);
}

BOOL CMFCODBCEXAMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMFCODBCEXAMView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	/*************************************************************코드추가*************************************************************/
	// ListCtrl에 이미지 넣기
	m_imageList.Create(48, 48, ILC_COLOR32, 5, 5);
	m_imageListSmall.Create(16, 16, ILC_COLOR32, 5, 5);

	m_imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_imageListSmall.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	m_listView.SetImageList(&m_imageList, LVSIL_NORMAL);
	m_listView.SetImageList(&m_imageListSmall, LVSIL_SMALL);


	//컬럼 정보 출력 
	m_listView.InsertColumn(0, _T("사원번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(1, _T("이름"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(2, _T("직업"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(3, _T("관리자"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(4, _T("입사일자"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(5, _T("급여"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(6, _T("상여금"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(7, _T("부서"), LVCFMT_LEFT, 150);

	// 체크박스
	DWORD dwExStyle = m_listView.GetExtendedStyle();
	m_listView.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// 사원 전체 목록을 얻는다.
	vector<CEmpPtr> empList = GetListEmp(m_db);

	int nRow = 0;

	for (const auto& pEmp : empList) {
		m_listView.InsertItem(nRow, pEmp->strEmpNo, 0);
		m_listView.SetItemText(nRow, 1, pEmp->strEName);
		m_listView.SetItemText(nRow, 2, pEmp->strJob);
		m_listView.SetItemText(nRow, 3, pEmp->strMgr);
		m_listView.SetItemText(nRow, 4, pEmp->strHireDate);
		m_listView.SetItemText(nRow, 5, pEmp->strSal);
		m_listView.SetItemText(nRow, 6, pEmp->strComm);
		m_listView.SetItemText(nRow, 7, pEmp->strDeptNo);
	}
}


// CMFCODBCEXAMView 인쇄

BOOL CMFCODBCEXAMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCODBCEXAMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCODBCEXAMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCODBCEXAMView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CMFCODBCEXAMView 진단

#ifdef _DEBUG
void CMFCODBCEXAMView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCODBCEXAMView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCODBCEXAMDoc* CMFCODBCEXAMView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCODBCEXAMDoc)));
	return (CMFCODBCEXAMDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCODBCEXAMView 메시지 처리기

/*************************************************************코드추가*************************************************************/
void CMFCODBCEXAMView::OnBnClickedButtonDelete()
{
	const int nCount = m_listView.GetItemCount();
	CString strEmpNo; // 삭제하는 EmpNo를 얻기 위함
	CString strSQL;

	// 화면 & DB에서 삭제
	CString strInParam;
	CArray<int, int> arr;

	// 삭제 위치와 삭제 사원 번호만 얻는다.
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			// 삭제 할 사원 번호를 얻는다.
			strEmpNo = m_listView.GetItemText(i, 0);

			strInParam += strEmpNo + _T(",");

			// 삭제할 사원번호의 위치를 배열에 추가한다.
			arr.Add(i);
		}
	}

	try {
		if (!strInParam.IsEmpty()) {
			// 뒤에 있는 (,)를 삭제한다.
			strInParam.Delete(strInParam.GetLength() - 1, 1);

			// SQL 삭제 구문을 생성한다.
			//strSQL.Format(_T("DELETE FROM emp WHERE EMPNO IN (%s)"), strInParam.GetBuffer());
			strSQL = _T("DELETE FROM emp WHERE EMPNO IN (") + strInParam + _T(")");

			// 트랜젝션 시작 : 데이터베이스 작업이 시작 될 때 // DML
			m_db.BeginTrans();

			m_db.ExecuteSQL(strSQL); // DML 구문

			// 트랜젝션 완료 // DML
			m_db.CommitTrans();

			// 화면에서 삭제 항목을 제거한다. - 예외가 발생되면 실행 안 함
			for (int i = 0; i < arr.GetSize(); i++) {
				// 목록에서 제거한다.
				m_listView.DeleteItem(arr.GetAt(i));
			}
		}
	}
	catch (const CException* p) {
		// 트랜젝션 복구 // DML
		m_db.Rollback();

		TCHAR szErr[100];
		p->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
	}
}


void CMFCODBCEXAMView::OnBnClickedButtonModify()
{
	const int nCount = m_listView.GetItemCount();
	CString strEmpNo;

	// 선택된 사원 번호를 얻는다.
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			strEmpNo = m_listView.GetItemText(i, 0);
			break;
		}
	}

	if (strEmpNo.IsEmpty()) {
		AfxMessageBox(_T("사원을 선택 해 주세요"));
		return;
	}

	// DB에서 사원번호에 대한 상세 정보를 얻는다
	// 1. 직원 목록을 얻는다. (관리자 선택 시 사용)
	// 2. 부서 목록을 얻는다. (부서 선택 시 사용)
	// 3. 사원번호로 사원 상세 정보를 얻는다. 


	// 1. 사원 전체 목록을 얻는다.
	vector<CEmpPtr> empList = GetListEmp(m_db);
	// 2. 부서 전체 목록을 얻는다.
	vector<CDeptPtr> deptList = GetListDept(m_db);
	// 3. 사원번호로 사원 상세 정보를 얻는다.
	CEmpPtr pEmp = GetEmp(m_db, strEmpNo);



	// 1. 대화상자에 사원 전체 목록, 부서 목록, 사원 상세 정보를 전달한다.
	// 2. 대화상자를 출력한다.
	CEmpDialog dlg;
	if (dlg.DoModal() == IDOK) {

	}


}
