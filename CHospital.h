#pragma once
class CHospital
{
public:
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
	CString strBusinessName; // 업태구분명
	CString strBusinessNickName; // 의료기관종별명
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

};

