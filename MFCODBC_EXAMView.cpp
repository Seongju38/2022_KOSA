
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


// CMFCODBCEXAMView

IMPLEMENT_DYNCREATE(CMFCODBCEXAMView, CFormView)

BEGIN_MESSAGE_MAP(CMFCODBCEXAMView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCODBCEXAMView::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CMFCODBCEXAMView 생성/소멸

CMFCODBCEXAMView::CMFCODBCEXAMView() noexcept
	: CFormView(IDD_MFCODBC_EXAM_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCODBCEXAMView::~CMFCODBCEXAMView()
{
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

	// 1. DB 연결
	// 2. SQL 구문 실행 
	// 3. SQL 구문 실행 결과 얻기
	// 4. 연결 종료

	// CDatabase 클래스 = DB 연결을 관리하는 클래스
	// CRecordSet 클래스 = SQL 구문을 실행하고 결과 집합을 관리하는 클래스

	// 1. DB 연결
	CDatabase db;
	BOOL bRet = db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (bRet) {
		//AfxMessageBox(_T("DB 연결 성공"));

		// 2. SQL 구문 실행
		CRecordset  rs(&db);
		//rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM emp"));
		rs.Open(CRecordset::forwardOnly,
			_T("SELECT a.empno, a.ename, a.job, b.ename mgr_name, \
				to_char(a.hiredate, 'YYYY-MM-DD'), to_char(a.sal, '99,999.0'), a.comm, c.dname \
			FROM emp a, emp b, dept c \
			WHERE a.mgr = b.empno(+) \
			AND a.deptno = c.deptno(+)"));

		//rs.MoveFirst();
		//rs.MoveNext();
		//rs.MoveLast();
		//rs.MovePrev();

		// 3. SQL 구문 실행 결과 얻기
		int nRow = 0;

		CDBVariant empNo;
		CString strEmpNo;
		CString strEName;
		CString strJob;
		CString strMgr;
		CString strHireDate;
		CString strSal;
		CString strComm;
		CString strDeptNo;

		// rs를 하나의 파일로 봄
		while (!rs.IsEOF()) {
			rs.GetFieldValue((short)0, empNo, SQL_C_SSHORT); // 숫자로 제어 가능
			//rs.GetFieldValue((short)0, strEName); // 인덱스로 데이터를 읽겠음 - 0만 쓰면 안 돼 : 0을 null로 판단함
			rs.GetFieldValue(1, strEName);
			rs.GetFieldValue(2, strJob);
			rs.GetFieldValue(3, strMgr);
			rs.GetFieldValue(4, strHireDate);
			rs.GetFieldValue(5, strSal);
			rs.GetFieldValue(6, strComm);
			rs.GetFieldValue(7, strDeptNo);

			//strEmpNo.Format(_T("%d"), empNo.m_iVal + 1000);
			strEmpNo.Format(_T("%d"), empNo.m_iVal);
			m_listView.InsertItem(nRow, strEmpNo, 0); // 첫번째 데이터에 이미지가 들어가게 함
			m_listView.SetItemText(nRow, 1, strEName);
			m_listView.SetItemText(nRow, 2, strJob);
			m_listView.SetItemText(nRow, 3, strMgr);
			m_listView.SetItemText(nRow, 4, strHireDate);
			m_listView.SetItemText(nRow, 5, strSal);
			m_listView.SetItemText(nRow, 6, strComm);
			m_listView.SetItemText(nRow, 7, strDeptNo);

			//AfxMessageBox(strValue);
	
			rs.MoveNext();

		}
		rs.Close();
	}
	else {
		AfxMessageBox(_T("DB 연결 실패"));
	}
	// DB 연결 종료
	db.Close();
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
	CDatabase db;
	BOOL bRet = db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (bRet) {
		CStringArray arr;

		for (int i = nCount - 1; i >= 0; --i) {
			if (m_listView.GetCheck(i)) {
				// 삭제 할 사원 번호를 얻는다.
				strEmpNo = m_listView.GetItemText(i, 0); // 삭제하는 EmpNo를 얻음

				// 삭제 할 사원을 SQL 구문을 생성한다.
				//strSQL.Format(_T("DELETE FROM emp WHERE empno = %s"), strEmpNo);
				// 삭제 SQL 구문을 실행한다.
				//db.ExecuteSQL(strSQL); // ExecuteSQL ( ) : DML 구문(insert, delete, update, merge)을 바로 전달할 수 있음
												 // 여러건을 삭제 할 때 그 여러 건만큼 실행됨 -> 성능저하

				// 삭제할 사원번호를 배열에 추가한다.
				arr.Add(strEmpNo);
				
				// 목록에서 제거한다.
				m_listView.DeleteItem(i);
			}
		}
		const int size = arr.GetSize();
		if (size != 0) {
			CString strInParam;

			// 만약 DELETE FROM emp WHERE EMPNO IN ( 1, 2, 3 ) 되어있다면, 
			//for (int i = 0; i < size; i++) {
			//	if (i != 0) { // 인덱스 0번째 앞에는 , 가 없으니까
			//		strInParam += _T(",");
			//	}
			//	strInParam += arr.GetAt(i);
			//}
			// 별로 좋은 코드는 아님 : 루프가 돌 때마다 if문을 사용하게 됨 -> 속도저하

			for (int i = 0; i < size; i++) {
				strInParam += arr.GetAt(i) + _T(","); // 마지막에 , 가 무조건 들어가게 되어있음
			}
			strInParam.Delete(strInParam.GetLength() - 1, 1); // 인덱스 0번째 앞에 있는 , 를 삭제하겠음

			// 만약 DELETE FROM emp WHERE EMPNO IN ( '1', '2', '3', '4', '5' ) 문자열로 되어있다면,
			//for (int i = 0; i < size; i++) {
			//	strInParam += _T("'") + arr.GetAt(i) + _T("',");
			//}
			//strInParam.Delete(strInParam.GetLength() - 1, 1);
			// 이 패턴을 익히는 게 좋음 : if문을 사용하지 않아도 됨

			strSQL.Format(_T("DELETE FROM emp WHERE EMPNO IN (%s)"), strInParam.GetBuffer());
			db.ExecuteSQL(strSQL);
		}
	}
	else {
		AfxMessageBox(_T("DB 연결 실패"));
	}
	// DB 연결 종료
	db.Close();
}
