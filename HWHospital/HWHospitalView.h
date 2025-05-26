
// HWHospitalView.h: CHWHospitalView 클래스의 인터페이스
//

#pragma once

#include "CHospital.h"
#include "CHospitalDialog.h"
#include "CMedicalSubject.h"
#include "CMediSubList.h"
#include "CHospitalStatus.h"
#include "CHospitalFindDlg.h"

class CHWHospitalView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CHWHospitalView() noexcept;
	DECLARE_DYNCREATE(CHWHospitalView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_HWHOSPITAL_FORM };
#endif

// 특성입니다.
public:
	CHWHospitalDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CHWHospitalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listView;
	CDatabase m_db;

	void SetHospitalListView(int nRow, const CHospitalPtr pHospital);
	void GetDBAllHospitalListView(vector<CHospitalPtr> HospitalList);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSearch();
};

#ifndef _DEBUG  // HWHospitalView.cpp의 디버그 버전
inline CHWHospitalDoc* CHWHospitalView::GetDocument() const
   { return reinterpret_cast<CHWHospitalDoc*>(m_pDocument); }
#endif

