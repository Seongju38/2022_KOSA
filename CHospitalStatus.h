
// 병원영업상태

#pragma once
class CHospitalStatus
{
public:
	CString strStatusValue;
	CString strStatusName;
};
using CHospitalStatusPtr = shared_ptr<CHospitalStatus>;

class CHospitalStatusDAO
{
private:
	CDatabase& m_db;
public:
	CHospitalStatusDAO(CDatabase& db) : m_db(db) {
	}

	vector<CHospitalStatusPtr> GetListHospitalStatus();
};

