// CHospitalDialog.cpp: 구현 파일
//

#include "pch.h"
#include "HWHospital.h"
#include "CHospitalDialog.h"
#include "afxdialogex.h"


// CHospitalDialog 대화 상자

IMPLEMENT_DYNAMIC(CHospitalDialog, CDialogEx)

//CHospitalDialog::CHospitalDialog(CWnd* pParent /*=nullptr*/)
//	: CDialogEx(IDD_HOSPITAL_INFO, pParent)
//	, m_strHospitalNo(_T(""))
//	, m_AuthDate(COleDateTime::GetCurrentTime())
//	, m_strStatusCode(_T(""))
//	, m_strDetaileStatusName(_T(""))
//	, m_strPhone(_T(""))
//	, m_strPostCode(_T(""))
//	, m_strAddress(_T(""))
//	, m_strRoadPostCode(_T(""))
//	, m_strRoadAddress(_T(""))
//	, m_strHospitalName(_T(""))
//	, m_strBusinessName(_T(""))
//	, m_strBusinessNickName(_T(""))
//	, m_strWorkerNum(_T(""))
//	, m_strRoomNum(_T(""))
//	, m_strBedNum(_T(""))
//{
//
//}

//CHospitalDialog::CHospitalDialog(vector<CHospitalPtr>& HList, CHospitalPtr pHospital, CWnd* pParent /*=nullptr*/)
//	: CDialogEx(IDD_HOSPITAL_INFO, pParent)
//	, m_HList(HList)
//	, m_pHospital(pHospital)
//
//	, m_strHospitalNo(_T(""))
//	, m_AuthDate(COleDateTime::GetCurrentTime())
//	, m_strStatusCode(_T(""))
//	, m_strDetaileStatusName(_T(""))
//	, m_strPhone(_T(""))
//	, m_strPostCode(_T(""))
//	, m_strAddress(_T(""))
//	, m_strRoadPostCode(_T(""))
//	, m_strRoadAddress(_T(""))
//	, m_strHospitalName(_T(""))
//	, m_strBusinessName(_T(""))
//	, m_strBusinessNickName(_T(""))
//	, m_strWorkerNum(_T(""))
//	, m_strRoomNum(_T(""))
//	, m_strBedNum(_T(""))
//{}

//CHospitalDialog::CHospitalDialog(vector<CHospitalPtr>& HList, vector<CHospitalStatusPtr>& HStatusList,
//											CHospitalPtr pHospital, CWnd* pParent /*=nullptr*/)
//	: CDialogEx(IDD_HOSPITAL_INFO, pParent)
//	, m_HList(HList)
//	, m_HStatusList(HStatusList)
//	, m_pHospital(pHospital)
//
//	, m_strHospitalNo(_T(""))
//	, m_AuthDate(COleDateTime::GetCurrentTime())
//	, m_strStatusCode(_T(""))
//	, m_strDetaileStatusName(_T(""))
//	, m_strPhone(_T(""))
//	, m_strPostCode(_T(""))
//	, m_strAddress(_T(""))
//	, m_strRoadPostCode(_T(""))
//	, m_strRoadAddress(_T(""))
//	, m_strHospitalName(_T(""))
//	, m_strBusinessName(_T(""))
//	, m_strBusinessNickName(_T(""))
//	, m_strWorkerNum(_T(""))
//	, m_strRoomNum(_T(""))
//	, m_strBedNum(_T(""))
//	, m_strStatusName(_T(""))
//	, m_strTreatmentSubject(_T(""))
//{}

CHospitalDialog::CHospitalDialog(vector<CHospitalPtr>& HList, vector<CHospitalStatusPtr>& HStatusList,
				map<CString, CString>& mapMedicalSubject, CHospitalPtr pHospital, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_INFO, pParent)
	, m_HList(HList)
	, m_HStatusList(HStatusList)
	, m_mapMedicalSubject(mapMedicalSubject)
	, m_pHospital(pHospital)

	, m_strHospitalNo(_T(""))
	, m_AuthDate(COleDateTime::GetCurrentTime())
	, m_strStatusCode(_T(""))
	, m_strDetaileStatusName(_T(""))
	, m_strPhone(_T(""))
	, m_strPostCode(_T(""))
	, m_strAddress(_T(""))
	, m_strRoadPostCode(_T(""))
	, m_strRoadAddress(_T(""))
	, m_strHospitalName(_T(""))
	, m_strBusinessName(_T(""))
	, m_strBusinessNickName(_T(""))
	, m_strWorkerNum(_T(""))
	, m_strRoomNum(_T(""))
	, m_strBedNum(_T(""))
	, m_strStatusName(_T(""))
	, m_strTreatmentSubject(_T(""))
{}

CHospitalDialog::~CHospitalDialog()
{
}

void CHospitalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HNO, m_strHospitalNo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_AuthDate);
	DDX_Text(pDX, IDC_EDIT_STATUSCODE, m_strStatusCode);
	DDX_Text(pDX, IDC_EDIT_STATUSNAME, m_strDetaileStatusName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_POSTNUM, m_strPostCode);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_ROADPOSTNUM, m_strRoadPostCode);
	DDX_Text(pDX, IDC_EDIT_ROADADDRESS, m_strRoadAddress);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strHospitalName);
	DDX_Text(pDX, IDC_EDIT_BUSINESSNAME, m_strBusinessName);
	DDX_Text(pDX, IDC_EDIT_BUSINESSNICKNAME, m_strBusinessNickName);
	DDX_Text(pDX, IDC_EDIT_WORKER, m_strWorkerNum);
	DDX_Text(pDX, IDC_EDIT_ROOM, m_strRoomNum);
	DDX_Text(pDX, IDC_EDIT_BED, m_strBedNum);
	DDX_Control(pDX, IDC_COMBO_STATUSNAME, m_comboStatusName);
	DDX_Control(pDX, IDC_COMBO_TREATSUB, m_comboTreatmentSubject);
	DDX_CBString(pDX, IDC_COMBO_STATUSNAME, m_strStatusName);
	DDX_CBString(pDX, IDC_COMBO_TREATSUB, m_strTreatmentSubject);
}


BEGIN_MESSAGE_MAP(CHospitalDialog, CDialogEx)
	ON_CBN_SELENDOK(IDC_COMBO_STATUSNAME, &CHospitalDialog::OnCbnSelendokComboStatusname)
	ON_CBN_SELENDOK(IDC_COMBO_TREATSUB, &CHospitalDialog::OnCbnSelendokComboTreatsub)
END_MESSAGE_MAP()


// CHospitalDialog 메시지 처리기


BOOL CHospitalDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_strHospitalNo = m_pHospital->strHospitalNo;
	m_AuthDate.ParseDateTime(m_pHospital->strAuthDate);
	m_strStatusCode = m_pHospital->strStatusCode;
	m_strDetaileStatusName = m_pHospital->strDetaileStatusName;
	m_strPhone = m_pHospital->strPhone;
	m_strPostCode = m_pHospital->strPostCode;
	m_strAddress = m_pHospital->strAddress;
	m_strRoadPostCode = m_pHospital->strRoadPostCode;
	m_strRoadAddress = m_pHospital->strRoadAddress;
	m_strHospitalName = m_pHospital->strHospitalName;
	m_strBusinessName = m_pHospital->strBusinessName;
	m_strBusinessNickName = m_pHospital->strBusinessNickName;
	m_strWorkerNum = m_pHospital->strWorkerNum;
	m_strRoomNum = m_pHospital->strRoomNum;
	m_strBedNum = m_pHospital->strBedNum;
	m_strStatusName = m_pHospital->strStatusName;
	m_strTreatmentSubject = m_pHospital->strTreatmentSubject;


	//CComboBox m_comboStatusName;
	int nIndex = 0;
	for (const auto& pStatus : m_HStatusList) {
		m_comboStatusName.InsertString(nIndex++, pStatus->strStatusName);
	}

	//CComboBox m_comboTreatmentSubject;
	nIndex = 0;
	for (const auto& pMediSub : m_mapMedicalSubject) {
		m_comboTreatmentSubject.InsertString(nIndex++, pMediSub.first);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHospitalDialog::OnCbnSelendokComboStatusname()
{
	// 현재 선택된 위치 얻음
	int nCurSel = m_comboStatusName.GetCurSel();
	if (nCurSel >= 0 && nCurSel <= m_HStatusList.size() - 1) {
		const CHospitalStatusPtr pStatus = m_HStatusList[nCurSel];
		//AfxMessageBox(pStatus->strStatusName);

		m_pHospital->strStatusName = pStatus->strStatusValue;
	}
}



// 진료과목내용명
void CHospitalDialog::OnCbnSelendokComboTreatsub()
{
	// 배열이 아니기에 쉽게 인덱스 값으로 현재 선택된 위치 얻기가 어려움
	// map 이니까 key를 찾아서 몇 번째인지 구해서 위치를 얻을 수 있으려나...?
}
