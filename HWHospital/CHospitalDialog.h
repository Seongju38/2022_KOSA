#pragma once


#include "CHospital.h";
#include "CHospitalStatus.h"
#include "CMedicalSubject.h"

// CHospitalDialog 대화 상자

class CHospitalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHospitalDialog)

public:
	//CHospitalDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	//CHospitalDialog(vector<CHospitalPtr>& HList, CHospitalPtr pHospital, CWnd* pParent = nullptr);
	/*CHospitalDialog(vector<CHospitalPtr>& HList, vector<CHospitalStatusPtr>& HStatusList,
		CHospitalPtr pHospital, CWnd* pParent = nullptr);*/
	CHospitalDialog(vector<CHospitalPtr>& HList, vector<CHospitalStatusPtr>& HStatusList,
		map<CString, CString>& mapMedicalSubject, CHospitalPtr pHospital, CWnd* pParent = nullptr);
	virtual ~CHospitalDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITAL_INFO };
#endif

private:
	bool IsEmpty(const CString& strText, LPCTSTR lpszMsg, UINT id) const;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	vector<CHospitalPtr>& m_HList;
	vector<CHospitalStatusPtr>& m_HStatusList;
	map<CString, CString>& m_mapMedicalSubject;
	CHospitalPtr m_pHospital; // 병원정보

	// 출력할 변수
	CString m_strHospitalNo;
	COleDateTime m_AuthDate;
	CString m_strStatusCode;
	CString m_strDetaileStatusName;
	CString m_strPhone;
	CString m_strPostCode;
	CString m_strAddress;
	CString m_strRoadPostCode;
	CString m_strRoadAddress;
	CString m_strHospitalName;
	CString m_strBusinessName;
	CString m_strBusinessNickName;
	CString m_strWorkerNum;
	CString m_strRoomNum;
	CString m_strBedNum;
	CComboBox m_comboStatusName;
	CString m_strStatusName;
	CComboBox m_comboTreatmentSubject;
	CString m_strTreatmentSubject;

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelendokComboStatusname();
	afx_msg void OnCbnSelendokComboTreatsub();
	afx_msg void OnBnClickedOk();

};
