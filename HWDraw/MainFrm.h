﻿
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	void SetMousePositionOutput(const CPoint& pt)
	{
		CString str;
		str.Format(_T("%d, %d"), pt.x, pt.y);
		m_wndStatusBar.SetWindowText(str);
	}

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


