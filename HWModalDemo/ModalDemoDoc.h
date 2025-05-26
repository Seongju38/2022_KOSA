
// ModalDemoDoc.h: CModalDemoDoc 클래스의 인터페이스
//


#pragma once

class CMember;
using CMemberPtr = shared_ptr<CMember>;

class CMember {
public:
	~CMember() {
		TRACE("소멸자\n");
	}
	
	CString m_strId;
	CString m_strName;
	int     m_nPostCode;
	CString m_strAddress;
	BOOL    m_bSex;
	CString m_strPhone1;
	CString m_strPhone2;
	CString m_strPhone3;
	int     m_nAge;
	int		m_nHobby;

	void operator=(CMemberPtr pMember) {
		m_strId = pMember->m_strId;
		m_strName = pMember->m_strName;
		m_nPostCode = pMember->m_nPostCode;
		m_strAddress = pMember->m_strAddress;
		m_bSex = pMember->m_bSex;
		m_strPhone1 = pMember->m_strPhone1;
		m_strPhone2 = pMember->m_strPhone2;
		m_strPhone3 = pMember->m_strPhone3;
		m_nAge = pMember->m_nAge;
		m_nHobby = pMember->m_nHobby;
	}
};
	

class CMemberMgr {
public:
	vector<CMemberPtr> m_array;

public:
	void InsertMember(CMemberPtr pMember) {
		m_array.push_back(pMember);
	}

	CMemberPtr GetMember(const CString strId) {
		auto& it = find_if(m_array.begin(), m_array.end(),
			[strId](auto& pMember) -> int {return pMember->m_strId == strId; });
		if (it != m_array.cend()) {
			return *it;
		}
		return nullptr;
	}

	bool DeleteMember(const CString strId) {
		const auto& it = find_if(m_array.cbegin(), m_array.cend(),
			[strId](const auto& pMember) -> int {return pMember->m_strId == strId; });
		if (it != m_array.cend()) {
			m_array.erase(it);
			return true;
		}
		return false;
	}
};

class CModalDemoDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CModalDemoDoc() noexcept;
	DECLARE_DYNCREATE(CModalDemoDoc)

// 특성입니다.
public:
	CMemberMgr	m_memberMgr;

// 작업입니다.
public:
	void InsertMember(CMemberPtr pMember) {
		m_memberMgr.InsertMember(pMember);
	}

	void DeleteMember(const CString& strId) {
		m_memberMgr.DeleteMember(strId);
	}

	CMemberPtr GetMember(const CString& strId) {
		return m_memberMgr.GetMember(strId);
	}

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CModalDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
