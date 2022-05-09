#pragma once
class CMedicalSubject
{
public:
	CString strTreatCode;
	CString strTreatName;
};
using CMedicalSubjectPtr = shared_ptr<CMedicalSubject>;

class CMedicalSubjectDAO
{
private:
	CDatabase& m_db;
public:
	CMedicalSubjectDAO(CDatabase& db) : m_db(db) {
	}

	vector<CMedicalSubjectPtr> GetListMedicalSubject();
	map<CString, CString> GetMapMedicalSubject();

};

