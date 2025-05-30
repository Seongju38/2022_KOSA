﻿
// MFCODBC_EXAMView.h: CMFCODBCEXAMView 클래스의 인터페이스
//

#pragma once


class CMFCODBCEXAMView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMFCODBCEXAMView() noexcept;
	DECLARE_DYNCREATE(CMFCODBCEXAMView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCODBC_EXAM_FORM };
#endif

// 특성입니다.
public:
	CMFCODBCEXAMDoc* GetDocument() const;

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
	virtual ~CMFCODBCEXAMView();
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
	
	/*************************************************************코드추가*************************************************************/
	CImageList m_imageList;
	CImageList m_imageListSmall;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonModify();

	// DB 연결
	CDatabase m_db;
};

#ifndef _DEBUG  // MFCODBC_EXAMView.cpp의 디버그 버전
inline CMFCODBCEXAMDoc* CMFCODBCEXAMView::GetDocument() const
   { return reinterpret_cast<CMFCODBCEXAMDoc*>(m_pDocument); }
#endif

