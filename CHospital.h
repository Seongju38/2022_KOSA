#pragma once
class CHospital
{
public:
	CHospital() :
		strHospitalNo(_T("")),
		strAuthDate(_T("")),
		strStatusName(_T("")),
		strStatusCode(_T("")),
		strDetaileStatusName(_T("")),
		strPhone(_T("")),
		strPostCode(_T("")),
		strAddress(_T("")),
		strRoadAddress(_T("")),
		strRoadPostCode(_T("")),
		strHospitalName(_T("")),
		strBusinessName(_T("")),
		strBusinessNickName(_T("")),
		strWorkerNum(_T("")),
		strRoomNum(_T("")),
		strBedNum(_T("")),
		strTreatmentSubject(_T(""))
	{

	}

	CString strHospitalNo;
	CString strAuthDate;
	CString strStatusName;
	CString strStatusCode;
	CString strDetaileStatusName;
	CString strPhone;
	CString strPostCode;
	CString strAddress;
	CString strRoadAddress;
	CString strRoadPostCode;
	CString strHospitalName;
	CString strBusinessName;
	CString strBusinessNickName;
	CString strWorkerNum;
	CString strRoomNum;
	CString strBedNum;
	CString strTreatmentSubject;
};
using CHospitalPtr = shared_ptr<CHospital>;

class CHospitalDAO {
private:
	CDatabase& m_db;
public:
	CHospitalDAO(CDatabase& db) : m_db(db) {
	}

	vector<CHospitalPtr> GetListHospital();
	CHospitalPtr GetDetailHospital(CString strHospitalNo);
	BOOL UpdateHospital(CHospitalPtr pHospital);
	BOOL InsertHospital(CHospitalPtr );
	vector<CHospitalPtr> GetListHospitalFind(CString strHospitalName, CString strHospitalPhone);
};




